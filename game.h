#include "team.h"

#pragma once
class game
{
private:
	team _home;
	team _away;
public:
	game(team home, team away);
	~game(void);
};

