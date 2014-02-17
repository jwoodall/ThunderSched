#include <QTextStream>
#include "schedule.h"

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
    QList<team*>* list1 = new QList<team*>;
    QList<team*>* list2 = new QList<team*>;

    QList<team*>** home = &list1;
    QList<team*>** away = &list2;

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
            list1->append(team1);
        }else{
            list2->append(team1);
        }
    }

    for (int day=1;day<=_num_games;day++){
        QList<game*>* dayList = new QList<game*>();
        generateGames(day, dayList, (*home), (*away));
        QList<team*>* temp = (*home);
        home = &(*away);
        away = &temp;
        if (day%2==0) shiftScheduleRight( *home );
        else shiftScheduleLeft( *home );

        printSchedule(QString("Game ")+QString::number(day), *dayList);
    }
    return 0;
}

void schedule::printSchedule( QString header, QList<game*> daySched )
{
    foreach(game* g1, daySched){
        QTextStream out(stdout);
        out << header << endl << endl;
        g1->print();
    }
}

void schedule::shiftScheduleRight( QList<team*>* home )
{
    team* temp = home->takeLast();
    home->insert(0,temp);
}

void schedule::shiftScheduleLeft( QList<team*>* home )
{
    team* temp = home->takeFirst();
    home->append(temp);
}

int schedule::generateGames(int day, QList<game*>* dayGames, const QList<team*>* home, const QList<team*>* away )
{
    if (home->count() != away->count()) return 1;   // if they are different sizes something is wrong.
    for (int ii=0; ii<home->count(); ii++){
        game* newGame = new game(home->value(ii),away->value(ii),day);
        dayGames->append(newGame);
    }

    return 0;
}
