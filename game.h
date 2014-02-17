#include "team.h"

#pragma once
class game
{
private:
    team* _home;
    team* _away;
    int _day;
public:
    bool _valid;

    game(team* home, team* away, int day);
	~game(void);
    void print();
    void validate(){_valid = _home!=_away;}
    QString dayString(){return QString::number(_day);}
    int day(){return _day;}
    team* home(){return _home;}
    team* away(){return _away;}
};

