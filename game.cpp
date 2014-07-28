#include <QTextStream>
#include <QFile>
#include "game.h"
#include "team.h"

game::game(team* home, team* away, int day)
	: _home(home)
	, _away(away)
    , _day(day)
{
    validate();
}


game::~game(void)
{
}

void game::print(QFile &file)
{
    QTextStream out(&file);
    out << "[url=" << _home->team_url() <<  "]" << _home->name() <<"[/url]";
    out << " (" << _home->raceName() << ") : ";
    out << "[url=" << _home->coach_url() <<  "]" << _home->coach() <<"[/url]";
    out << " [b]vs[/b] ";
    out << "[url=" << _away->team_url() <<  "]" << _away->name() <<"[/url]";
    out << " (" << _away->raceName() << ") : ";
    out << "[url=" << _away->coach_url() <<  "]" << _away->coach() <<"[/url]";
    out << endl;
}
