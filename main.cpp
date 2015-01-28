
#include <QCoreApplication>
#include <QStringList>
#include <QString>
#include <QTextStream>
#include <QtSql>

#include "team.h"
#include "game.h"
#include "schedule.h"
#include "sql_queries.h"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
    QTextStream out(stdout);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("thunderbowl.sqlite");
    if (!db.open()) {
        QStringList r = QSqlDatabase::drivers();
        QString drivers = r.join(", ");
        return 1;
    }

    out << "ThunderSchedule version 0.1" << endl;

    int games = 10;
    int num_teams_b = 0;
    int num_teams_c = 0;

    QString baseFileName = "D://project//thunder_noui//output//season18//3//";

    QString filename = baseFileName + "thundersched_18_B.txt";

    schedule newSched_B(filename, games);
    newSched_B = schedule(filename, games);


    // B -League Season 18
    newSched_B.addTeam( new team(ChaosDwarf,"Phlegraean Marauders","Gollumullog","50","281") );
    newSched_B.addTeam( new team(Slann,"Freezin Reign","Nevyn","56","400") );
    newSched_B.addTeam( new team(Chaos,"Freaks and Weirdos","Spaceman Spiff","14","18") );
    newSched_B.addTeam( new team(WoodElf,"Druid's Dream","Gazgul","30","314") );
    newSched_B.addTeam( new team(Orc,"Waauugghh Mash'een ","Dah Koach","99","378") );
    newSched_B.addTeam( new team(Human,"Silly English Kannniggits","poundfist","6","425") );
    newSched_B.addTeam( new team(ChaosDwarf,"40 Grinders","Blammaham","53","113") );
    newSched_B.addTeam( new team(HighElf,"Chrace White-Lions","Keggiemckill","10","423") );
    newSched_B.addTeam( new team(Slann,"Leaps of Faith","Warpstone","22","324") );
    newSched_B.addTeam( new team(ChaosDwarf,"Darkland Warriors","Dylanator","19","46") );
    newSched_B.addTeam( new team(ChaosPact,"Powers of Pain","Badcuz","112","408") );
    newSched_B.addTeam( new team(WoodElf,"Monarch's' Minions","UrukHai","97","364") );
    newSched_B.addTeam( new team(Chaos,"Warlords","Sallacious","15","19") );
    newSched_B.addTeam( new team(HighElf,"Eataine Excelsiors","endycarus","47","71") );
    newSched_B.addTeam( new team(Norse,"Ravers Re-Booted","dva13","71","228") );
    newSched_B.addTeam( new team(Chaos,"Need to Feed","Redman","21","419") );
    newSched_B.addTeam( new team(Human,"Verde Slackers","Smallpox","104","359") );
    newSched_B.addTeam( new team(Orc,"Rangoon Typhoon","MacPhee","51","435") );


/*   Season 17
    newSched_B.addTeam( new team(ChaosDwarf,"Apocalypto","Rimmer","7","380") );
    newSched_B.addTeam( new team(Chaos,"Freaks and Weirdos","Spaceman Spiff","14","18") );
    newSched_B.addTeam( new team(Dwarf,"Bad News Beards","Bear","32","198") );
    newSched_B.addTeam( new team(Orc,"Waauugghh Mash'een ","Dah Koach","99","378") );
    newSched_B.addTeam( new team(Human,"Verde Slackers","Smallpox","104","359") );
    newSched_B.addTeam( new team(Slann,"Freezing Reign","Nevyn","56","400") );
    newSched_B.addTeam( new team(Lizardmen,"Serpentine Glory","Gimli","31","222") );
    newSched_B.addTeam( new team(Norse,"F'N Givers","Lord Chaos","13","79") );
//    newSched_B.addTeam( new team(Slann,"Wholly Highsteppers","Majyk","92","208") );
    newSched_B.addTeam( new team(DarkElf,"Hydra Lords","Harbinger","43","63") );
    newSched_B.addTeam( new team(Orc,"Angmar Express","Gustav","102","323") );
    newSched_B.addTeam( new team(ChaosDwarf,"40 Grinders","Blammaham","53","113") );
    newSched_B.addTeam( new team(ChaosDwarf,"Phlegraean Marauders","Gollumullog","50","281") );
//    newSched_B.addTeam( new team(Chaos,"Popcorn Fools","Osirus11","23","325") );
    newSched_B.addTeam( new team(ChaosDwarf,"Hashut's Hellfires","Wedge22","18","235") );
    newSched_B.addTeam( new team(Lizardmen,"Pax Britannia","Gazgul","30","171") );
    newSched_B.addTeam( new team(HighElf,"Eataine Excelsiors","Endycarus","47","71") );
    newSched_B.addTeam( new team(Slann,"Leaps of Faith","Warpstone","22","324") );
    newSched_B.addTeam( new team(Necromantic,"Full Death Metal Jacket","VampireLogan","93","210") );
    newSched_B.addTeam( new team(DarkElf,"Storm Crows","Ocrumsprug","74","226") );
*/

    num_teams_b = newSched_B.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams_b)+" teams."  << endl;

    newSched_B.generate();


    // C-League Season 17
    filename = baseFileName + "thundersched_18_C.txt";

    schedule newSched_C(filename, games);
    newSched_C = schedule(filename, games);

    newSched_C.addTeam( new team(Orc,"Rage Quittaz","Ocrumsprug","74","450") );
    newSched_C.addTeam( new team(Human,"Paladins","Gimli","31","455") );
    newSched_C.addTeam( new team(DarkElf,"Brotherhood of Mutant Supremacy","Rimmer","7","451") );
    newSched_C.addTeam( new team(HighElf,"Les Fées Vertes","Eric.R","116","") );
    newSched_C.addTeam( new team(ChaosDwarf,"Dark Ruin","Khysanth","115","449") );
    newSched_C.addTeam( new team(Khemri,"Rigor Mortis","Wedge22","18","430") );
    newSched_C.addTeam( new team(Necromantic,"The Adams Family","Nitnit","52","458") );
    newSched_C.addTeam( new team(Undead,"Grave Mistake","Mr. Gordon","62","456") );
    newSched_C.addTeam( new team(Vampire,"World Of Darkness","VampireLogan","18","459") );
    newSched_C.addTeam( new team(Orc,"Black Sun Squad","Lowecore","83","460") );
    newSched_C.addTeam( new team(Slann,"SkySlaanders","Darkangeldave","48","457") );
    newSched_C.addTeam( new team(Lizardmen,"","Trentusdementus","77","") );

    /*Season 17
    newSched_C.addTeam( new team(Necromantic,"RakNaFobYa","dva13","71","417") );
    newSched_C.addTeam( new team(Undead,"Grave Diggerz","Mr. Bloodwiser","91","431") );
    newSched_C.addTeam( new team(HighElf,"Chrace White-Lions","keggiemckill","10","423") );
    newSched_C.addTeam( new team(Norse,"Sons of Freedom","NitNit","52","418") );
    newSched_C.addTeam( new team(DarkElf,"Dirty Elven Scoundrels","Trentusdementus","77","426") );
    newSched_C.addTeam( new team(Lizardmen,"GatorBoyz","Sallacious","15","424") );
    newSched_C.addTeam( new team(HighElf,"Smurf that Smurf!","Edwad","76","421") );
    newSched_C.addTeam( new team(Chaos,"Need to Feed","Redman","21","419") );
    newSched_C.addTeam( new team(DarkElf,"Stiletto Heels ","Bubbles","9","434") );
    newSched_C.addTeam( new team(Human,"Silly English Kannniggits.","Poundfist","6","425") );
    newSched_C.addTeam( new team(Nurgle,"Newly Infected","Squirrel","103","427") );
    newSched_C.addTeam( new team(DarkElf,"Zardok Pitfighters","Cyrust59","60","438") );
    newSched_C.addTeam( new team(Undead,"Six Feet Under","Dylanator","19","441") );
//    newSched_C.addTeam( new team(Chaos,"bringers of pain","1000 Deaths","105","428") );
    newSched_C.addTeam( new team(Nurgle,"Slow Drips","Luvverman","27","443") );
    newSched_C.addTeam( new team(Orc,"Reavers go West","Pythrr","114","439") );
    newSched_C.addTeam( new team(Undead,"Boneyard Brutes","Khysanth","115","433") );
    newSched_C.addTeam( new team(Orc,"Rangoon Typhoon","MacPhee","51","435") );
    newSched_C.addTeam( new team(HighElf,"Sizzlin' Spirals","Badcuz","112","440") );
    newSched_C.addTeam( new team(ChaosPact,"The Expendables","Darkangeldave","48","437") );
    newSched_C.addTeam( new team(Amazon,"Titty Twister","UrukHai","97","436") );
*/
    num_teams_c = newSched_C.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams_c)+" teams."  << endl;
    newSched_C.generate();

    // Minor Season 18
    filename = baseFileName + "thundersched_18_Minor.txt";

    schedule newSched_M(filename, 5);
    newSched_M = schedule(filename, 5);

    newSched_M.addTeam( new team(ChaosPact,"Null Zone all Blanks","Endycarus","47","394") );
    newSched_M.addTeam( new team(Khemri,"Old Kingdom Pharaohs","Gimli","31","386") );
    newSched_M.addTeam( new team(Norse,"Sons of Freedom","NitNit","52","418") );
    newSched_M.addTeam( new team(DarkElf,"Blood of Heroes","Gollumullog","50","122") );
    newSched_M.addTeam( new team(HighElf,"Mighty High","Wedge22","18","255") );
    newSched_M.addTeam( new team(Necromantic,"RakNaFobYa","dva13","71","417") );
    newSched_M.addTeam( new team(Vampire,"The Dark Knights Regen!","Warpstone","22","401") );
    newSched_M.addTeam( new team(ChaosPact,"Nocturnal Parasites","Mr. Gordon","62","393") );
    newSched_M.addTeam( new team(Nurgle,"Slow Drips","Luvverman","27","443") );
    newSched_M.addTeam( new team(Chaos,"Slaanesh Scions","Darkangeldave","48","288") );
    newSched_M.addTeam( new team(Undead,"Six Feet Under","Dylanator","19","441") );
    newSched_M.addTeam( new team(ChaosPact,"Positive Thinking","VampireLogan","18","243") );

/* Minors 17
 *     newSched_M.addTeam( new team(Khemri,"Old Kingdom Pharaohs","Gimli","31","386") );
    newSched_M.addTeam( new team(ChaosPact,"Null Zone all Blanks","Endycarus","47","394") );
    newSched_M.addTeam( new team(Halfling,"Puggy's Revenge","Majyk","92","383") );
    newSched_M.addTeam( new team(Goblin,"Star Player Killerz","Mr. Bloodwiser","91","391") );
    newSched_M.addTeam( new team(Chaos,"Demon Legion","Sallacious","15","402") );
    newSched_M.addTeam( new team(Goblin,"Villainous Kabal","Ocrumsprug","74","252") );
    newSched_M.addTeam( new team(Amazon,"Odelay","NitNit","52","379") );
    newSched_M.addTeam( new team(Halfling,"No Expectations","Bear","32","251") );
    newSched_M.addTeam( new team(ChaosDwarf,"Taco Bull","Edwad","76","253") );
    newSched_M.addTeam( new team(Human,"Dm Electric","Dylanator","19","392") );
    newSched_M.addTeam( new team(ChaosPact,"Powers of Pain","Badcuz","112","408") );
    newSched_M.addTeam( new team(Norse,"Ravers Rebooted","dva13","71","228") );
    newSched_M.addTeam( new team(Vampire,"The Dark Knights Regen!","Warpstone","22","401") );
    newSched_M.addTeam( new team(Chaos,"Slaanesh Scions","Darkangeldave","48","288") );
    newSched_M.addTeam( new team(ChaosPact,"Positive Thinking","VampireLogan","93","243") );
    newSched_M.addTeam( new team(Human,"Backdoor Blitzers","Lord Chaos","13","410") );
    newSched_M.addTeam( new team(HighElf,"Mighty High","Wedge22","18","255") );
    newSched_M.addTeam( new team(HighElf,"Swiftsure Royals","Blammaham","53","293") );
*/
    int num_teams_m = newSched_M.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(5)+" games, "+QString::number(num_teams_m)+" teams."  << endl;
    newSched_M.generate();

    return 0;
}

// schedule used for 18/10 sched
/*
 *     schedule newSched_B(games);
    newSched_B = schedule(games);


    // B -League Season 17
    newSched_B.addTeam( new team(Lizardmen,"Bad News Beards","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Kamz Krusherz","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Freaks and Weirdos","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Porcland Jailblazers","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Ravers Rebooted","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Sjoktraken Jarls","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Stake to the Heart","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Passholes","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Eataine Excelsiors","Coach") );

    newSched_B.addTeam( new team(Lizardmen,"Full Death Metal Jacket","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Praag Flesheaters","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Broncosaurus Slayers","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Hashuts Hellfires","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Pax Britannia","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Lucky Charms","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Hogan's Heroes","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Rivendell Roughriders","Coach") );
    newSched_B.addTeam( new team(Lizardmen,"Hydra Lords","Coach") );


    num_teams_b = newSched_B.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams_b)+" teams."  << endl;

    newSched_B.generate();
*/
