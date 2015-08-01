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
    if (team.startsWith("Amaz",Qt::CaseInsensitive)) return Amazon;
    if (team == "Chaos") return Chaos;
    if (team.startsWith( "ChaosDwar",Qt::CaseInsensitive)) return ChaosDwarf;
    if (team.startsWith( "ChaosPact",Qt::CaseInsensitive)) return ChaosPact;
    if (team.startsWith( "DarkEl",Qt::CaseInsensitive)) return DarkElf;
    if (team.startsWith( "Dwar",Qt::CaseInsensitive)) return Dwarf;
    if (team.startsWith( "El",Qt::CaseInsensitive)) return Elf;
    if (team.startsWith( "Goblin",Qt::CaseInsensitive)) return Goblin;
    if (team.startsWith( "Halfling",Qt::CaseInsensitive)) return Halfling;
    if (team.startsWith( "HighEl",Qt::CaseInsensitive)) return HighElf;
    if (team.startsWith( "Human",Qt::CaseInsensitive)) return Human;
    if (team.startsWith( "Khemri",Qt::CaseInsensitive)) return Khemri;
    if (team.startsWith( "Lizardm",Qt::CaseInsensitive)) return Lizardmen;
    if (team.startsWith( "Necro",Qt::CaseInsensitive)) return Necromantic;
    if (team.startsWith( "Norse",Qt::CaseInsensitive)) return Norse;
    if (team.startsWith( "Nurgle",Qt::CaseInsensitive)) return Nurgle;
    if (team.startsWith( "Ogre",Qt::CaseInsensitive)) return Ogre;
    if (team.startsWith( "Orc",Qt::CaseInsensitive)) return Orc;
    if (team.startsWith( "Ork",Qt::CaseInsensitive)) return Orc;
    if (team.startsWith( "Skaven",Qt::CaseInsensitive)) return Skaven;
    if (team.startsWith( "Slann",Qt::CaseInsensitive)) return Slann;
    if (team.startsWith( "Undead",Qt::CaseInsensitive)) return Undead;
    if (team.startsWith( "Underworld",Qt::CaseInsensitive)) return Underworld;
    if (team.startsWith( "Vampire",Qt::CaseInsensitive)) return Vampire;
    if (team.startsWith( "WoodEl",Qt::CaseInsensitive)) return WoodElf;
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

