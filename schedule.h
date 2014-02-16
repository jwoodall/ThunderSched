#pragma once
#include "team.h"
#include "game.h"
#include <QList>

class schedule
{
private:
	int _num_games;
	int _max_teams;
    QList<team*> _teams;

public:
	schedule(int num_games);
	~schedule(void);
	int generate();
    int addTeam(team* team1);
    int generateGames(const QList<game*>& day, const QLinkedList<team*>& home, QLinkedList<team*>& away );
};

