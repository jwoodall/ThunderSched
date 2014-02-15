#include "team.h"
#include <QString>

team::team()
{
}

team::team( const team& team1 )
{
	_race = team1._race;
	_name = team1._name;
}

team::team(int race, QString name)
	: _race(race)
	, _name(name)
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
