#include <QTextStream>
#include <QSet>
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
    QTextStream out(stdout);
    int count=0;
    int alternate = sched_fine;
    QList<team*>* list1 = new QList<team*>;
    QList<team*>* list1_alt = new QList<team*>;
    QList<team*>* list2 = new QList<team*>;
    QList<team*>* list2_alt = new QList<team*>;

    QList<team*>** home = &list1;
    QList<team*>** away = &list2;

    int num_teams = _teams.count();
    if (num_teams % 2 == 1){
        // can't use odd number of teams
        out << "Schedule is invalid, can't use odd number of teams." << endl;
        return 1;
    }
    if (num_teams <= _num_games){
        // can't create schedule for teams less than number of games
        out << QString("Schedule is invalid, can't create schedule for less teams than number of games: ")+QString::number(num_teams)+"<="+QString::number(_num_games) << endl;
        return 1;
    }
    if (num_teams < 2*_num_games){
        // schedule will need modified arrays
        if ((num_teams / 2)%2 == 1){
            alternate = sched_alt_odd;
        }else{
            alternate = sched_alt_even;
        }
    }

    // fill home away
    foreach(team* team1, _teams){
        count++;
        if(count<=num_teams/2){
            list1->append(team1);
        }else{
            list2->append(team1);
        }
    }
    if (alternate != sched_fine){
        foreach(team* team1, _teams){
            count++;
            if(count%2==1){
                // odd
                list1_alt->append(team1);
            }else{
                //even
                list2_alt->append(team1);
            }
        }
    }
    if (alternate == sched_alt_odd){
        // can't create schedule for this yet, need a better algorithm
        out << QString("Can't create schedule for alternate odd schedule: ")+QString::number(num_teams)+" teams / games:"+QString::number(_num_games) << endl;
        return 1;
    }
    bool dontShiftFirst = false;
    for (int day=1;day<=_num_games;day++){
        QList<game*>* dayList = new QList<game*>();
        generateGames(day, dayList, (*home), (*away));
        if (day%2==0){
            if ((alternate != sched_fine)
                    &&(day+1>num_teams/2)){
                home = &list1_alt;
                away = &list2_alt;
                if (dontShiftFirst) {
                    shiftAltScheduleLeft( *home );
                }
                dontShiftFirst = true;
            }else{
                home = &list1;
                away = &list2;
                shiftScheduleRight( *home );
            }
        }
        else{
            if ((alternate != sched_fine)\
                    &&(day+1>num_teams/2)){
                home = &list2_alt;
                away = &list1_alt;
                if (dontShiftFirst) {
                    shiftAltScheduleRight( *home );
                }
                dontShiftFirst = true;
            }else{
                home = &list2;
                away = &list1;
                shiftScheduleLeft( *home );
            }
        }

//        printSchedule(QString("Game ")+QString::number(day), *dayList);
    }
    if (!validateSchedule()){
        QTextStream out(stdout);
        out << "Schedule is invalid." << endl;
        return 1;
    }
    return 0;
}

void schedule::printSchedule( QString header, QList<game*> daySched )
{
    QTextStream out(stdout);
    out << endl << endl;
    out << header << endl;
    foreach(game* g1, daySched){
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

void schedule::shiftAltScheduleRight( QList<team*>* home )
{
    int pos = (home->count()/2);
    team* temp = home->takeLast();
    home->insert(pos,temp);
    temp = home->takeAt(pos-1);
    home->insert(0,temp);
}

void schedule::shiftAltScheduleLeft( QList<team*>* home )
{
    int pos = (home->count()/2)-1;
    team* temp = home->takeFirst();
    home->insert(pos,temp);
    temp = home->takeAt(pos+1);
    home->insert(home->count(),temp);
}

int schedule::generateGames(int day, QList<game*>* dayGames, const QList<team*>* home, const QList<team*>* away )
{
    if (home->count() != away->count()) return 1;   // if they are different sizes something is wrong.
    for (int ii=0; ii<home->count(); ii++){
        game* newGame = new game(home->value(ii),away->value(ii),day);
        dayGames->append(newGame);
        _games << newGame;
    }
    return 0;
}
bool schedule::validateSchedule()
{
    QTextStream out(stdout);
    out << "Validating..." << endl;

    out << "  Count teams" << endl;
    foreach(team* tm, _teams){
        int count = getGameCount(tm);
        out << tm->name() << ": " << count << " total games" << endl;
        if (count != _num_games) return false;
        if (!verifyTeam(tm)) return false;
    }
    out << endl;
    foreach(game* gm, _games){
        if (!gm->_valid){
            out << "A game is invalid: " << gm->dayString() << " with " << gm->home()->name() <<  endl;
            return false;
        }
    }
    return true;
}
int schedule::getGameCount(team* team1)
{
    int count = 0;
    foreach(game* gm, _games){
        if ((gm->away() == team1) ||
                (gm->home() == team1)) count++;
    }
    return count;
}

bool schedule::verifyTeam(team* team1)
{
    QList<team*> opponents;
    foreach(game* gm, _games){
        if (gm->away() == team1) opponents << gm->home();
        if (gm->home() == team1) opponents << gm->away();
    }
    if (opponents.toSet().count() != opponents.count()){
        QTextStream out(stdout);
        out << team1->name() << " has duplicate opponents." << endl;
        return false;
    }
    return true;
}
