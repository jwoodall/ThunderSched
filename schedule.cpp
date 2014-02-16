#include "schedule.h"
#include <QLinkedList>

schedule::schedule(int num_games)
	:_num_games(num_games)
    , _max_teams(100)
{
}


schedule::~schedule(void)
{
    while(_teams.count() > 0){
      delete (_teams.takeAt(0));   //Always delete element 0
    }
}

int schedule::addTeam(team* team1)
{
    // check size of team
    if ( _teams.count() >= _max_teams ) {
        return 1;
    }
    // add team
    _teams.append(team1);
    return 0;
}

int schedule::generate(void)
{
    QLinkedList<team*> _home;
    QLinkedList<team*> _away;

    int num_teams = _teams.count();
    if (num_teams % 2 == 1){
        // can't use odd number of teams
        return 1;
    }
    int count=0;
    // fill home away
    foreach(team* team1, _teams){
        count++;
        if(count<=num_teams/2){
            _home << team1;
        }else{
            _away << team1;
        }
    }

    // Generate day 1
    QList<game*> day1;
    generateGames(day1, _home, _away);

    return 0;
}

int schedule::generateGames(const QList<game*>& day, const QLinkedList<team*>& home, QLinkedList<team*>& away )
{
    return 0;
}
