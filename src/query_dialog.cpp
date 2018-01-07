#include "query_dialog.h"
#include "ui_query_dialog.h"

#include <QtCore>

#include "db.h"
#include "message_dialog.h"


QueryDialog::QueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryDialog)
{
    ui->setupUi(this);
    init();

    ui->comboBox_queries->addItems(queryTitles);
}

QueryDialog::~QueryDialog()
{
    delete ui;
}


void QueryDialog::init()
{
    queryTitles = QStringList({
        "Query 1",
        "Query 2",
        "Query 3",
        "Query 4",
        "Query 5",
        "Query 6",
        "Query 7",
        "Query 8",
        "Query 9",
        "Query 10",
        "Query 11",
        "Query 12",
        "Query 13",
        "Query 14",
        "Query 15",
        "Query 16",
        "Query 17",
        "Query 18",
        "Query 19",
        "Query 20"
    });

    queryDescriptions = QStringList({
        "یافتن نام و نام خانوادگی تمام سربازهایی که در ارتشی با نام 'Army_0' عضویت دارند.",
        "یافتن نام میزان مقاومت وسایل نقلیه ای که کمتر از 70 درصد سالم اند و متعلق به ارتشی به نام 'Army_3' هستند",
        "یافتن نوع لباسی که فرمانده ارتش 'Army_0' می‌پوشد.",
        "یافتن شعاع میدان نبردی که ارتشی با نام 'Army_0' متعلق به آن است.",
        "یافتن نام اسلحه‌هایی که سربازی با نام 'Trooper_FName_11' می‌تواند داشته باشد.",
        "لیست مرگ و میر  میدان نبرد پایگاهی با نام 'Base_0'.",
        "اسلحه‌ هایی با سزعت شلیک بیشتر از 7 چه نوع مهماتی می‌تواند شلیک کند.",
        "مصرف سوخت وسایل نقلیه‌ای با سرعت بیشتر از 80 که در پایگاهی با نام 'Base_0' قرار دارند.",
        "موقعیت استحکامات غیر طبیعی مربوط به میدان نبردی یا شعاع بیشتر از 50.",
        "میزان جراحت تیراندازی هایی که نوع هدفشان سرباز بوده است.",
        "یافتن نام و نام خانوادگی سربازانی که مهارت از نوع 0 دارند",
        "نام تمام سلاح هایی که وزن مهماتشان از 50 کیلوگرم بیشتر است",
        "یافتن نام مهمات و ظرفیت سلاح مربوط به آن در تمامی سلاح هایی که سرعت آن ها 10 متر بر ثانیه است و طول هر یک از مهمات بیشتر از یک متر باشد.",
        "یافتن حداکثر سرعت ماشین هایی که قدرت دفاعی بیشتر از75 دارند و متعلق به پایگاهی با بیش از 150 سرباز هستند.",
        "تعداد سرنشینان وسایل نقلیه ای که حداقل 70 لیتر سوخت میگیرند و شتاب حداکثری آن ها 10 متر بر مجذور ثانیه است.",
        "نام تمام انبار هایی که لباسی بزرگتر از سایز 8 دارند.",
        "نوع تمام محافظت هایی که در میدان نبردی با شعاع بیشتر از 105 متر انجام شده اند.",
        "یافتن درجه تمام سربازان مجرد",
        "یافتن نام و نام خانوادگی سربازانی که وزن بالای 90 کیلو گرم و قد زیر 182 سانتی متر دارند",
        "یافتن نام تمام پایگاه هایی که در میدان نبردی به بزرگی شعاع بیش از 104 متر حضور داشته و وسیله نقلیه ای با حداکثر ظرفیت سوخت بیش از 85 لیتر دارند",
    });

    queries = QStringList({                            
        "select troopers.first_name, troopers.last_name "
        "from armies, army_has_trooper, troopers "
        "where army_has_trooper.trooper_fk = troopers.id and "
        "army_has_trooper.army_fk = armies.id and armies.name = 'Army_0'",

        "select vehicles.armor "
        "from armies, army_has_vehicle, vehicles "
        "where army_has_vehicle.vehicle_fk = vehicles.id and "
        "army_has_vehicle.army_fk = armies.id and armies.name = 'Army_3' "
        "and vehicles.health < 70",

        "select suits.type "
        "from armies, troopers, trooper_has_suit, suits "
        "where armies.commander_fk = troopers.id and "
        "trooper_has_suit.trooper_fk = troopers.id and "
        "trooper_has_suit.suit_fk = suits.id and armies.name = 'Army_0'",

        "select battlefields.radius "
        "from battlefields, bases, armies "
        "where armies.name = 'Army_0' and armies.base_fk = bases.id and "
        "bases.battlefield_fk = battlefields.id",

        "select weapons.name "
        "from weapons, armies, army_has_weapon, army_has_trooper, "
        "troopers "
        "where weapons.id = army_has_weapon.weapon_fk and armies.id = "
        "army_has_weapon.army_fk and armies.id = army_has_trooper.army_fk "
        "and army_has_trooper.trooper_fk = troopers.id and "
        "troopers.first_name = 'Trooper_FName_11'",

        "select troopers.first_name, troopers.last_name, deaths.reason "
        "from troopers, armies, bases, deaths, army_has_trooper "
        "where deaths.trooper_fk = troopers.id and troopers.id = "
        "army_has_trooper.trooper_fk and army_has_trooper.army_fk = "
        "armies.id and armies.base_fk = bases.id and bases.name = "
        "'Base_0'",

        "select ammo.name, ammo.type "
        "from ammo, weapons, weapon_canuse_ammo "
        "where weapons.fire_speed > 9 and weapons.id = "
        "weapon_canuse_ammo.weapon_fk and weapon_canuse_ammo.ammo_fk = "
        "ammo.id",

        "select vehicles.fuel_consuming_unit "
        "from vehicles, base_has_vehicle, bases "
        "where vehicles.id = base_has_vehicle.vehicle_fk and "
        "base_has_vehicle.base_fk = bases.id and bases.name = 'Base_0'",

        "select fortifications.position_latitude, "
        "fortifications.position_longitude "
        "from fortifications, battlefields "
        "where fortifications.battlefield_fk = battlefields.id and "
        "battlefields.radius > 50",

        "select strikes.damage "
        "from targets, strike_to_target, strikeswhere targets.id = strike_to_target.target_fk and "
        "strike_to_target.strike_fk = strikes.id and targets.type = 0",

        "select troopers.first_name, troopers.last_name "
        "from troopers, trooper_skills "
        "where trooper_skills.skill = 0 and trooper_skills.trooper_fk = troopers.id ",

        "select weapons.name "
        "from weapons, ammo, weapon_canuse_ammo "
        "where ammo.weight > 60 and ammo.id = weapon_canuse_ammo.ammo_fk and weapon_canuse_ammo.weapon_fk = weapons.id",

        "select ammo.name, weapons.count "
        "from weapons, ammo, weapon_canuse_ammo "
        "where ammo.length = 1 and weapons.fire_speed = 10 and weapons.id = weapon_canuse_ammo.weapon_fk "
        "and ammo.id = weapon_canuse_ammo.ammo_fk",

        "select vehicles.max_speed "
        "from bases, base_has_vehicle, vehicles "
        "where vehicles.armor > 75 and vehicles.id = base_has_vehicle.vehicle_fk and base_has_vehicle.base_fk = bases.id "
        "and bases.trooper_capacity > 150",

        "select vehicles.max_passengers "
        "from vehicles "
        "where vehicles.fuel_max_capacity > 85 and vehicles.max_acceleration > 10",

        "select bases.name "
        "from base_has_suit, bases, suits "
        "where suits.size > 8 and suits.id = base_has_suit.suit_fk and base_has_suit.base_fk = bases.id",

        "select fortifications.type "
        "from battlefields, fortifications "
        "where battlefields.radius > 105 and battlefields.id = fortifications.battlefield_fk",

        "select troopers.grade "
        "from troopers "
        "where troopers.is_single = 1",

        "select troopers.first_name, troopers.last_name "
        "from troopers "
        "where troopers.height < 1.82 and troopers.weight > 90",

        "select bases.name "
        "from bases, battlefields, vehicles, base_has_vehicle "
        "where vehicles.fuel_max_capacity > 85 and battlefields.radius >= 105 "
        "and vehicles.id = base_has_vehicle.vehicle_fk and bases.id = base_has_vehicle.base_fk and bases.battlefield_fk = battlefields.id",
    });
}

void QueryDialog::on_pushButton_doQuery_clicked()
{
    QueryData result = DB::instance()->query(ui->plainTextEdit_query->toPlainText());

    if (!(result.error.isEmpty() && result.error.isNull()))
    {
        MessageDialog::instance()->err(result.error);
        return;
    }

    ui->tableWidget_data->setColumnCount(0);
    ui->tableWidget_data->setRowCount(0);
    ui->tableWidget_data->setColumnCount(result.columns.size());
    ui->tableWidget_data->setHorizontalHeaderLabels(result.columns);

    for (int row = 0; row < result.rows.size(); row++)
    {
        ui->tableWidget_data->insertRow(row);
        for (int col = 0; col < result.rows[row].size(); col++)
        {
            auto x = new QTableWidgetItem(result.rows[row][col].toString());
            x->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_data->setItem(row, col, x);
        }
    }

    ui->tableWidget_data->resizeColumnsToContents();
    ui->tableWidget_data->resizeRowsToContents();
    for (int i = 0; i < ui->tableWidget_data->columnCount(); i++)
        ui->tableWidget_data->setColumnWidth(i, ui->tableWidget_data->columnWidth(i) + 20);
}

void QueryDialog::on_comboBox_queries_currentIndexChanged(int index)
{
    ui->label_queryDescription->setText(queryDescriptions[index]);
    ui->plainTextEdit_query->setPlainText(queries[index]);
}
