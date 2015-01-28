#include <QString>
#include <QStringList>

#pragma once

enum myTeams {
	Amazon
	, Chaos
	, ChaosDwarf
	, ChaosPact
	, DarkElf
	, Dwarf
	, Elf
	, Goblin
	, Halfling
	, HighElf
	, Human
	, Khemri
	, Lizardmen
	, Necromantic
	, Norse
	, Nurgle
	, Ogre
	, Orc
	, Skaven
	, Slann
	, Undead
	, Underworld
	, Vampire
	, WoodElf
};

static int getMyTeam(QString team){
    if (team == "Amazon") return Amazon;
    if (team == "Chaos") return Chaos;
    if (team == "ChaosDwarf") return ChaosDwarf;
    if (team == "ChaosPact") return ChaosPact;
    if (team == "DarkElf") return DarkElf;
    if (team == "Dwarf") return Dwarf;
    if (team == "Elf") return Elf;
    if (team == "Goblin") return Goblin;
    if (team == "Halfling") return Halfling;
    if (team == "HighElf") return HighElf;
    if (team == "Human") return Human;
    if (team == "Khemri") return Khemri;
    if (team == "Lizardmen") return Lizardmen;
    if (team == "Necromantic") return Necromantic;
    if (team == "Norse") return Norse;
    if (team == "Nurgle") return Nurgle;
    if (team == "Ogre") return Ogre;
    if (team == "Orc") return Orc;
    if (team == "Skaven") return Skaven;
    if (team == "Slann") return Slann;
    if (team == "Undead") return Undead;
    if (team == "Underworld") return Underworld;
    if (team == "Vampire") return Vampire;
    if (team == "WoodElf") return WoodElf;
    return -1;
}

class team
{
private:
    static QString _team_url;
    static QString _coach_url;
	QString _name;
    QString _coach;
    QString _coach_id;
    QString _team_id;
    int _race;

public:
	team();
	team( const team& team1 );
    team(int race, QString name, QString coach,  QString coach_id,  QString team_id);
    team(int race, QString name, QString coach);
    ~team(void);

	 team& operator=( const team& rhs );
	 bool operator!=( const team& rhs );
	 bool operator==( const team& rhs );

     QString name() {return _name;};
     QString team_id() {return _team_id;};
     QString coach_id() {return _coach_id;};
     QString coach() {return _coach;};
     int race() {return _race;};
     QString raceName() {return Races.value(_race);};

     QString team_url() {
         return QString(_team_url)+_team_id;
     };
     QString coach_url() {
         return QString(_coach_url)+_coach_id;
     };

     static QStringList Races;
};

