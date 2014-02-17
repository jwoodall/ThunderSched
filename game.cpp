#include <QTextStream>
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

void game::print()
{
    QTextStream out(stdout);
    out << _home->name();
    out << " (" << _home->race() << ") : ";
    out << _home->coach();
    out << " vs ";
    out << _away->name();
    out << " (" << _away->race() << ") : ";
    out << _away->coach();
    out << endl;
}
