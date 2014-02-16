#include "game.h"
#include "team.h"

game::game(team* home, team* away, int day)
	: _home(home)
	, _away(away)
    , _day(day)
{
}


game::~game(void)
{
}
