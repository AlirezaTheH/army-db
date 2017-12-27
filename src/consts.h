#ifndef CONSTS_H
#define CONSTS_H

#include <QString>


const QString USER_ROLE = "USER_ROLE";
const QString DATETIME_PATTERN = "^(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2})$";

const QString ALLOW_NULL = "ALLOW_NULL";
const QString MINIMUM = "MINIMUM";
const QString MAXIMUM = "MAXIMUM";
const QString MINIMUM_LENGTH = "MINIMUM_LENGTH";
const QString MAXIMUM_LENGTH = "MAXIMUM_LENGTh";
const QString LIMIT_MINIMUM = "LIMIT_MINIMUM";
const QString LIMIT_MAXIMUM = "LIMIT_MAXIMUM";
const QString PATTERN = "PATTERN";
const QString ENUM_ATTRS = "ENUM_ATTRS";
const QString LIST_ATTRS = "LIST_ATTRS";


const QStringList ARMY_FORCE_TYPES({
    "Air Force",
    "Land Force",
    "Sea Force"
});

const QStringList ARMY_SIZE_TYPES({
    "Army",
    "Battalion"
});

const QStringList TROOPER_TYPES({
    "Commander",
    "Soldier"
});

const QStringList TROOPER_SKILLS({
    "RPG",
    "Translator",
    "Medic",
    "Sniper"
});

const QStringList FORTIFICATION_TYPES({
    "Sea",
    "Mountain"
});

const QStringList VEHICLE_TYPES({
    "Jeep",
    "Tank",
    "Bulldozer",
});

const QStringList VEHICLE_FUEL_TYPES({
    "Petrol",
    "Gas"
});

const QStringList AMMO_TYPES({
    "Bomb",
    "Bullet",
});

const QStringList AMMO_SURFACE_MATERAIL({
    "Aluminium",
    "Titanium"
});

const QStringList AMMO_EXPLOSION_MATERIAL({
    "Gunpowder",
    "TNT",
    "Ammonium Nitrate"
});

const QStringList WEAPON_TYPES({
    "Colt",
    "Sniper",
    "RPG"
});

const QStringList WEAPON_MODELS({
    "M1",
    "T300",
    "MP5"
});

const QStringList SUIT_TYPES({
    "Swim",
    "Pilot",
    "Combat"
});


#endif // CONSTS_H
