#include "team.h"

#pragma once
class game
{
private:
    team* _home;
    team* _away;
    int _day;
public:
    game(team* home, team* away, int day);
	~game(void);
    void print();
};

