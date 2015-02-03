#include "team.h"
#include <QString>

QStringList team::Races = QStringList()<< "Amazon"<<"Chaos"<<"ChaosDwarf"<<"ChaosPact"<<"DarkElf"<<"Dwarf"<<"Elf"<<"Goblin"<<"Halfling"<<"HighElf"<<"Human"<<"Khemri"<<"Lizardmen"<<"Necromantic"<<"Norse"<<"Nurgle"<<"Ogre"<<"Orc"<<"Skaven"<<"Slann"<<"Undead"<<"Underworld"<<"Vampire"<<"WoodElf";
QString team::_team_url = "http://tbsn.thunderbowl.ca/index.php?section=objhandler&type=1&obj=2&obj_id=";
QString team::_coach_url = "http://tbsn.thunderbowl.ca/index.php?section=objhandler&type=1&obj=3&obj_id=";

team::team()
{
}

team::team( const team& team1 )
{
	_race = team1._race;
	_name = team1._name;
}

team::team(int race, QString name, QString coach)
    : _race(race)
    , _name(name)
    , _coach(coach)
{
}

team::team(int race, QString name, QString coach,  QString coach_id,  QString team_id)
	: _race(race)
	, _name(name)
    , _coach(coach)
    , _coach_id(coach_id)
    , _team_id(team_id)
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

team team::getTeamFromHtml(const QString &html) {
    team new_team;
    return new_team;
}
