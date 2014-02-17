#include "team.h"
#include <QString>

QStringList team::Races = QStringList()<< "Amazon"<<"Chaos"<<"ChaosDwarf"<<"ChaosPact"<<"DarkElf"<<"Dwarf"<<"Elf"<<"Goblin"<<"Halfling"<<"HighElf"<<"Human"<<"Khemri"<<"Lizardmen"<<"Necromantic"<<"Norse"<<"Nurgle"<<"Ogre"<<"Orc"<<"Skaven"<<"Slann"<<"Undead"<<"Underworld"<<"Vampire"<<"WoodElf";

team::team()
{
}

team::team( const team& team1 )
{
	_race = team1._race;
	_name = team1._name;
}

team::team(int race, const char* name, const char* coach)
	: _race(race)
	, _name(name)
    , _coach(coach)
{
}


team::~team(void)
{
}

team& team::operator=( const team& rhs )
{
	_race = rhs._race;
	_name = rhs._name;

	return *this;
}

bool team::operator!=( const team& rhs )
{
	if (_race == rhs._race) return false;
	if (_name == rhs._name) return false;
	return true;
}

bool team::operator==( const team& rhs )
{
	if (_race != rhs._race) return false;
	if (_name != rhs._name) return false;
	return true;
}
