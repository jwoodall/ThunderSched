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
	QString _name;
    QString _coach;
    int _race;

public:
	team();
	team( const team& team1 );
    team(int race, const char* name, const char* coach);
	~team(void);

	 team& operator=( const team& rhs );
	 bool operator!=( const team& rhs );
	 bool operator==( const team& rhs );

     QString name() {return _name;};
     QString coach() {return _coach;};
     QString race() {return Races.value(_race);};

     static QStringList Races;
};

