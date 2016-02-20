#include <QTextStream>
#include <QSet>
#include <QFile>
#include <QDir>
#include "schedule.h"

schedule::schedule(QString filename, int num_games)
	:_num_games(num_games)
    , _max_teams(100)
    , _filename (filename)
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

    // calculate bash/finesse
    _bash << Chaos << ChaosDwarf << ChaosPact << Dwarf << Khemri << Lizardmen << Necromantic << Norse << Nurgle << Ogre << Orc << Undead;
    _finesse << Amazon << DarkElf << Elf << Goblin << Halfling << HighElf << Human << Skaven << Slann << Vampire << WoodElf << Underworld;

//    _bash << Chaos << ChaosDwarf << Dwarf << Khemri<< Necromantic << Ogre << Orc << Undead  << Norse  << Human;
//    _finesse << Amazon << DarkElf << Elf << Goblin << Halfling << HighElf << Nurgle << Skaven << Slann << Vampire << WoodElf << Underworld << Lizardmen << ChaosPact;

    //
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
    if ((num_teams == 6)&&(_num_games == 5)){
         return generate5for6();
    }

    if (alternate == sched_alt_odd){
        if ((num_teams == 18)&&(_num_games == 10)) return generate18for10();
        // can't create schedule for this yet, need a better algorithm
        out << QString("Can't create schedule for alternate odd schedule: ")+QString::number(num_teams)+" teams / games:"+QString::number(_num_games) << endl;
        return 1;
    }
    if ((num_teams == 12)&&(_num_games == 10)){
         return generate12for10();
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
    QFile file(_filename);
    if(file.open(QFile::Append | QFile::Text))
    {
        file.seek(file.size());
        QTextStream out(&file);
        out << endl << endl;
        out << header << endl;
        foreach(game* g1, daySched){
            g1->print(file);
        }
        file.close();
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

bool schedule::validateGames()
{
    foreach(game* gm, _games){
        int count_home = getHomeGameCount(gm->home());
        int count_away = getAwayGameCount(gm->away());
        if ((count_home > _num_games/2) && (count_away > _num_games/2)){
            // swap
            gm->swap();
        }
        if ((count_home < _num_games/2) && (count_away < _num_games/2)){
            // swap
            gm->swap();
        }
    }
    return true;
}

bool schedule::validateSchedule()
{
    validateGames();

    QTextStream out(stdout);
    out << "Validating..." << endl;

    out << "  Count teams" << endl;
    foreach(team* tm, _teams){
        int count = getGameCount(tm);
        int bash = 0;
        int finesse = 0;
        int non = getStyleGameCount(tm, &bash, &finesse);
        int count_bash = getBashGameCount(tm);
        int count_finesse = getFinesseGameCount(tm);

        int count_home = getHomeGameCount(tm);
        int count_away = getAwayGameCount(tm);


        out << tm->name() << ": " << count << " total games" << ": " << count_home << "H/" << count_away << "A";
        if (count == 5) {
//            Minor league no home/away
            out << endl;
        }else{
            out << ": " << count_bash << "B/" << count_finesse << "F"<< endl;
        }

        if (count != _num_games) return false;
        if (!verifyTeam(tm)) return false;
    }
    out << endl;

    // Generate Day Lists
    //delete the file before beginning
    QDir dir(_filename);
    dir.remove(_filename);
    for(int day=1; day<=_num_games;++day){
        QList<game*>* dayList = new QList<game*>();

        foreach(game* gm, _games){
            if (gm->day() == day){
                dayList->append(gm);
            }
        }

        printSchedule(QString("Game ")+QString::number(day), *dayList);
        delete dayList;
    }
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

int schedule::getAwayGameCount(team* team1)
{
    int count = 0;
    foreach(game* gm, _games){
        if (gm->away() == team1) count++;
    }
    return count;
}

int schedule::getHomeGameCount(team* team1)
{
    int count = 0;
    foreach(game* gm, _games){
        if (gm->home() == team1) count++;
    }
    return count;
}


int schedule::getStyleGameCount(team* team1, int* bash, int* finesse)
{
    int count = 0;
    int non = 0;
    foreach(game* gm, _games){
        if (gm->away() == team1){
            int race = gm->home()->race();
            if (_bash.contains(race)) *bash++;
            else if (_finesse.contains(race)) *finesse++;
            else {
                non++; }
        }
        else if (gm->home() == team1){
            int race = gm->away()->race();
            if (_bash.contains(race)) *bash++;
            else if (_finesse.contains(race)) *finesse++;
            else {
                non++; }
        }
        else {
            non++;
        }
    }
    return non;
}

int schedule::getBashGameCount(team* team1)
{
    int count = 0;
    foreach(game* gm, _games){
        if (gm->away() == team1){
            if (_bash.contains(gm->home()->race())) count++;
        }
        if (gm->home() == team1){
            if (_bash.contains(gm->away()->race())) count++;
        }
    }
    return count;
}

int schedule::getFinesseGameCount(team* team1)
{
    int count = 0;
    foreach(game* gm, _games){
        if (gm->away() == team1){
            if (_finesse.contains(gm->home()->race())) count++;
        }
        if (gm->home() == team1){
            if (_finesse.contains(gm->away()->race())) count++;
        }
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


int schedule::generate18for10(void)
{
    QTextStream out(stdout);
    int count=0;
    QList<team*>* list1 = new QList<team*>;
    QList<team*>* list2 = new QList<team*>;


    int num_teams = _teams.count();

    // populate the lists
    foreach(team* team1, _teams){
        count++;
        if(count<=num_teams/2){
            list1->append(team1);
        }else{
            list2->append(team1);
        }
    }

    QList<game*>* dayList = new QList<game*>();
    int day = 1;
    generateGames(day, dayList, (list1), (list2));
////    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 2;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[9]);
    list1->append(_teams[12]);
    list1->append(_teams[2]);
    list1->append(_teams[3]);
    list1->append(_teams[10]);
    list1->append(_teams[6]);
    list1->append(_teams[8]);
    list1->append(_teams[13]);
    list1->append(_teams[5]);

    list2->append(_teams[11]);
    list2->append(_teams[1]);
    list2->append(_teams[4]);
    list2->append(_teams[0]);
    list2->append(_teams[7]);
    list2->append(_teams[17]);
    list2->append(_teams[14]);
    list2->append(_teams[16]);
    list2->append(_teams[15]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 3;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[4]);
    list2->append(_teams[0]);
    list1->append(_teams[9]);
    list2->append(_teams[8]);
    list1->append(_teams[17]);
    list2->append(_teams[1]);
    list1->append(_teams[2]);
    list2->append(_teams[13]);
    list1->append(_teams[5]);
    list2->append(_teams[3]);
    list1->append(_teams[15]);
    list2->append(_teams[10]);
    list1->append(_teams[16]);
    list2->append(_teams[11]);
    list1->append(_teams[12]);
    list2->append(_teams[7]);
    list1->append(_teams[6]);
    list2->append(_teams[14]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 4;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[9]);
    list2->append(_teams[6]);
    list1->append(_teams[1]);
    list2->append(_teams[7]);
    list1->append(_teams[17]);
    list2->append(_teams[2]);
    list1->append(_teams[16]);
    list2->append(_teams[3]);
    list1->append(_teams[14]);
    list2->append(_teams[4]);
    list1->append(_teams[0]);
    list2->append(_teams[5]);
    list1->append(_teams[13]);
    list2->append(_teams[10]);
    list1->append(_teams[11]);
    list2->append(_teams[15]);
    list1->append(_teams[12]);
    list2->append(_teams[8]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 5;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[10]);
    list2->append(_teams[9]);
    list1->append(_teams[11]);
    list2->append(_teams[1]);
    list1->append(_teams[12]);
    list2->append(_teams[2]);
    list1->append(_teams[4]);
    list2->append(_teams[3]);
    list1->append(_teams[17]);
    list2->append(_teams[0]);
    list1->append(_teams[7]);
    list2->append(_teams[8]);
    list1->append(_teams[16]);
    list2->append(_teams[6]);
    list1->append(_teams[15]);
    list2->append(_teams[14]);
    list1->append(_teams[13]);
    list2->append(_teams[5]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 6;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[9]);
    list2->append(_teams[16]);
    list1->append(_teams[14]);
    list2->append(_teams[1]);
    list1->append(_teams[6]);
    list2->append(_teams[2]);
    list1->append(_teams[3]);
    list2->append(_teams[7]);
    list1->append(_teams[17]);
    list2->append(_teams[4]);
    list1->append(_teams[0]);
    list2->append(_teams[13]);
    list1->append(_teams[10]);
    list2->append(_teams[5]);
    list1->append(_teams[8]);
    list2->append(_teams[11]);
    list1->append(_teams[15]);
    list2->append(_teams[12]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 7;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[9]);
    list2->append(_teams[12]);
    list1->append(_teams[4]);
    list2->append(_teams[1]);
    list1->append(_teams[2]);
    list2->append(_teams[0]);
    list1->append(_teams[10]);
    list2->append(_teams[3]);
    list1->append(_teams[11]);
    list2->append(_teams[6]);
    list1->append(_teams[7]);
    list2->append(_teams[14]);
    list1->append(_teams[13]);
    list2->append(_teams[17]);
    list1->append(_teams[5]);
    list2->append(_teams[8]);
    list1->append(_teams[15]);
    list2->append(_teams[16]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 8;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[4]);
    list2->append(_teams[9]);
    list1->append(_teams[1]);
    list2->append(_teams[0]);
    list1->append(_teams[10]);
    list2->append(_teams[2]);
    list1->append(_teams[3]);
    list2->append(_teams[11]);
    list1->append(_teams[14]);
    list2->append(_teams[12]);
    list1->append(_teams[6]);
    list2->append(_teams[13]);
    list1->append(_teams[7]);
    list2->append(_teams[5]);
    list1->append(_teams[15]);
    list2->append(_teams[17]);
    list1->append(_teams[8]);
    list2->append(_teams[16]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 9;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[17]);
    list2->append(_teams[9]);
    list1->append(_teams[1]);
    list2->append(_teams[13]);
    list1->append(_teams[2]);
    list2->append(_teams[5]);
    list1->append(_teams[3]);
    list2->append(_teams[15]);
    list1->append(_teams[16]);
    list2->append(_teams[4]);
    list1->append(_teams[0]);
    list2->append(_teams[8]);
    list1->append(_teams[14]);
    list2->append(_teams[10]);
    list1->append(_teams[11]);
    list2->append(_teams[7]);
    list1->append(_teams[12]);
    list2->append(_teams[6]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 10;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[11]);
    list2->append(_teams[10]);
    list1->append(_teams[14]);
    list2->append(_teams[9]);
    list1->append(_teams[1]);
    list2->append(_teams[6]);
    list1->append(_teams[8]);
    list2->append(_teams[2]);
    list1->append(_teams[13]);
    list2->append(_teams[3]);
    list1->append(_teams[5]);
    list2->append(_teams[4]);
    list1->append(_teams[0]);
    list2->append(_teams[15]);
    list1->append(_teams[16]);
    list2->append(_teams[12]);
    list1->append(_teams[7]);
    list2->append(_teams[17]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    if (!validateSchedule()){
        QTextStream out(stdout);
        out << "Schedule is invalid." << endl;
        return 1;
    }
    return 0;
}

int schedule::generate12for10(void)
{
    QTextStream out(stdout);
    int count=0;
    QList<team*>* list1 = new QList<team*>;
    QList<team*>* list2 = new QList<team*>;


    int num_teams = _teams.count();

    // populate the lists
    foreach(team* team1, _teams){
        count++;
        if(count<=num_teams/2){
            list1->append(team1);
        }else{
            list2->append(team1);
        }
    }

    QList<game*>* dayList = new QList<game*>();
    int day = 1;
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 2;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[4]);
    list2->append(_teams[6]);
    list1->append(_teams[5]);
    list2->append(_teams[8]);
    list1->append(_teams[3]);
    list2->append(_teams[0]);
    list1->append(_teams[10]);
    list2->append(_teams[11]);
    list1->append(_teams[2]);
    list2->append(_teams[7]);
    list1->append(_teams[1]);
    list2->append(_teams[9]);

    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 3;
    list1->clear();
    list2->clear();
    dayList->clear();
    list1->append(_teams[0]);
    list2->append(_teams[7]);
    list1->append(_teams[6]);
    list2->append(_teams[8]);
    list1->append(_teams[2]);
    list2->append(_teams[11]);
    list1->append(_teams[1]);
    list2->append(_teams[4]);
    list1->append(_teams[5]);
    list2->append(_teams[9]);
    list1->append(_teams[3]);
    list2->append(_teams[10]);

    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 4;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[2]);
    list2->append(_teams[6]);
    list1->append(_teams[8]);
    list2->append(_teams[3]);
    list1->append(_teams[0]);
    list2->append(_teams[4]);
    list1->append(_teams[9]);
    list2->append(_teams[10]);
    list1->append(_teams[7]);
    list2->append(_teams[5]);
    list1->append(_teams[1]);
    list2->append(_teams[11]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 5;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[6]);
    list2->append(_teams[9]);
    list1->append(_teams[11]);
    list2->append(_teams[8]);
    list1->append(_teams[5]);
    list2->append(_teams[0]);
    list1->append(_teams[4]);
    list2->append(_teams[7]);
    list1->append(_teams[1]);
    list2->append(_teams[10]);
    list1->append(_teams[3]);
    list2->append(_teams[2]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 6;
    list1->clear();
    list2->clear();
    dayList->clear();
    list1->append(_teams[11]);
    list2->append(_teams[4]);
    list1->append(_teams[0]);
    list2->append(_teams[9]);
    list1->append(_teams[6]);
    list2->append(_teams[10]);
    list1->append(_teams[3]);
    list2->append(_teams[7]);
    list1->append(_teams[5]);
    list2->append(_teams[2]);
    list1->append(_teams[1]);
    list2->append(_teams[8]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 7;
    list1->clear();
    list2->clear();
    dayList->clear();
    list1->append(_teams[9]);
    list2->append(_teams[4]);
    list1->append(_teams[5]);
    list2->append(_teams[1]);
    list1->append(_teams[2]);
    list2->append(_teams[10]);
    list1->append(_teams[8]);
    list2->append(_teams[7]);
    list1->append(_teams[6]);
    list2->append(_teams[3]);
    list1->append(_teams[0]);
    list2->append(_teams[11]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 8;
    list1->clear();
    list2->clear();
    dayList->clear();
    list1->append(_teams[10]);
    list2->append(_teams[7]);
    list1->append(_teams[9]);
    list2->append(_teams[11]);
    list1->append(_teams[0]);
    list2->append(_teams[8]);
    list1->append(_teams[6]);
    list2->append(_teams[5]);
    list1->append(_teams[2]);
    list2->append(_teams[1]);
    list1->append(_teams[4]);
    list2->append(_teams[3]);

    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 9;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[0]);
    list2->append(_teams[10]);
    list1->append(_teams[8]);
    list2->append(_teams[9]);
    list1->append(_teams[11]);
    list2->append(_teams[7]);
    list1->append(_teams[1]);
    list2->append(_teams[6]);
    list1->append(_teams[5]);
    list2->append(_teams[3]);
    list1->append(_teams[4]);
    list2->append(_teams[2]);

    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 10;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[7]);
    list2->append(_teams[9]);
    list1->append(_teams[10]);
    list2->append(_teams[8]);
    list1->append(_teams[11]);
    list2->append(_teams[6]);
    list1->append(_teams[4]);
    list2->append(_teams[5]);
    list1->append(_teams[3]);
    list2->append(_teams[1]);
    list1->append(_teams[2]);
    list2->append(_teams[0]);
    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    if (!validateSchedule()){
        QTextStream out(stdout);
        out << "Schedule is invalid." << endl;
        return 1;
    }
    return 0;
}


int schedule::generate5for6(void)
{
    QTextStream out(stdout);
    int count=0;
    QList<team*>* list1 = new QList<team*>;
    QList<team*>* list2 = new QList<team*>;


    int num_teams = _teams.count();

    QList<game*>* dayList = new QList<game*>();
    int day = 1;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[1]);    list2->append(_teams[2]);
    list1->append(_teams[4]);    list2->append(_teams[0]);
    list1->append(_teams[3]);    list2->append(_teams[5]);

    generateGames(day, dayList, (list1), (list2));
    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 2;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[1]);    list2->append(_teams[3]);
    list1->append(_teams[2]);    list2->append(_teams[0]);
    list1->append(_teams[4]);    list2->append(_teams[5]);

    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 3;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[1]);    list2->append(_teams[4]);
    list1->append(_teams[2]);    list2->append(_teams[3]);
    list1->append(_teams[5]);    list2->append(_teams[0]);

    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 4;
    list1->clear();
    list2->clear();
    dayList->clear();
    list1->append(_teams[1]);    list2->append(_teams[5]);
    list1->append(_teams[2]);    list2->append(_teams[4]);
    list1->append(_teams[3]);    list2->append(_teams[0]);


    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    day = 5;
    list1->clear();
    list2->clear();
    dayList->clear();

    list1->append(_teams[1]);    list2->append(_teams[0]);
    list1->append(_teams[2]);    list2->append(_teams[5]);
    list1->append(_teams[3]);    list2->append(_teams[4]);

    generateGames(day, dayList, (list1), (list2));
//    printSchedule(QString("Game ")+QString::number(day), *dayList);

    if (!validateSchedule()){
        QTextStream out(stdout);
        out << "Schedule is invalid." << endl;
        return 1;
    }
    return 0;
}
