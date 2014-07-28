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
    team(int race, const char* name, const char* coach,  const char* coach_id,  const char* team_id);
    team(int race, const char* name, const char* coach);
    ~team(void);

	 team& operator=( const team& rhs );
	 bool operator!=( const team& rhs );
	 bool operator==( const team& rhs );

     QString name() {return _name;};
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

