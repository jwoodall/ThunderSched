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

void game::swap()
{
    team* temp = _home;
    _home = _away;
    _away = temp;
}

void game::print(QFile &file)
{
    QTextStream out(&file);
    if (_home->team_id()==""){
        out << _home->name();
    }else{
        out << "[url=" << _home->team_url() <<  "]" << _home->name() <<"[/url]";
    }

    out << " (" << _home->raceName() << ") : ";

    if (_home->coach_id()==""){
        out << _home->coach();
    }else{
        out << "[url=" << _home->coach_url() <<  "]" << _home->coach() <<"[/url]";
    }
    out << " [b]vs[/b] ";

    if (_away->team_id()==""){
        out << _away->name();
    }else{
        out << "[url=" << _away->team_url() <<  "]" << _away->name() <<"[/url]";
    }

    out << " (" << _away->raceName() << ") : ";

    if (_away->coach_id()==""){
        out << _away->coach();
    }else{
        out << "[url=" << _away->coach_url() <<  "]" << _away->coach() <<"[/url]";
    }
    out << endl;
}
