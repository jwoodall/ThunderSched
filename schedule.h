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
    QList<game*> _games;

    QList<int> _bash;
    QList<int> _finesse;

    enum alternate_sched { sched_fine
                           , sched_alt_odd
                           , sched_alt_even
                         };

public:
	schedule(int num_games);
	~schedule(void);
	int generate();
    int addTeam(team* team1);
    int numberTeams(){return _teams.count();}
    int generateGames(int day, QList<game*>* dayGames, const QList<team*>* home, const QList<team*>* away );
    void shiftScheduleRight( QList<team*>* home );
    void shiftScheduleLeft( QList<team*>* home );
    void shiftAltScheduleRight( QList<team*>* home );
    void shiftAltScheduleLeft( QList<team*>* home );
    void printSchedule( QString header, QList<game*> daySched );
    bool validateSchedule();
    int getGameCount(team* team1);
    int getBashGameCount(team* team1);
    int getFinesseGameCount(team* team1);
    bool verifyTeam(team* team1);
};

