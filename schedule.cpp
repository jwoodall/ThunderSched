#include "schedule.h"
#include <QList>

schedule::schedule(int num_games)
	:_num_games(num_games)
{
}


schedule::~schedule(void)
{
}

int schedule::generate(void)
{
	return 1;
}

int schedule::addTeam(team team1)
{
	// check size of team
	if ( _teams.count() >= _max_teams ) {
		return 1;
	}
	// add team
	_teams << team1;
	return 0;
}
