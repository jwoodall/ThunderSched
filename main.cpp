
#include <QCoreApplication>
#include <QStringList>
#include <QString>
#include <QTextStream>

#include "team.h"
#include "game.h"
#include "schedule.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
    QTextStream out(stdout);
    out << "ThunderSchedule version 0.1" << endl;

    int games = 10;
    int num_teams_b = 0;
    int num_teams_c = 0;

    schedule newSched_B(games);
    newSched_B = schedule(games);


    // B -League Season 17
    newSched_B.addTeam( new team(ChaosDwarf,"Apocalypto","Rimmer","7","380") );
    newSched_B.addTeam( new team(Chaos,"Freaks and Weirdos","Spaceman Spiff","18","14") );
    newSched_B.addTeam( new team(Dwarf,"Bad News Beards","Bear","32","198") );
    newSched_B.addTeam( new team(Orc,"Waauugghh Mash'een ","Dah Koach","99","378") );
    newSched_B.addTeam( new team(Human,"Verde Slackers","Smallpox","104","359") );
    newSched_B.addTeam( new team(Slann,"Freezing Reign","Nevyn","56","400") );
    newSched_B.addTeam( new team(Lizardmen,"Serpentine Glory","Gimli","31","222") );
    newSched_B.addTeam( new team(Norse,"F'N Givers","Lord Chaos","13","79") );
    newSched_B.addTeam( new team(Slann,"Wholly Highsteppers","Majyk","92","208") );
    newSched_B.addTeam( new team(Orc,"Angmar Express","Gustav","102","323") );
    newSched_B.addTeam( new team(ChaosDwarf,"40 Grinders","Blammaham","53","113") );
    newSched_B.addTeam( new team(Chaos,"Popcorn Fools ","Osirus11","23","325") );
    newSched_B.addTeam( new team(ChaosDwarf,"Hashut's Hellfires","Wedge22","18","235") );
    newSched_B.addTeam( new team(Lizardmen,"Pax Britannia","Gazgul","30","171") );
    newSched_B.addTeam( new team(HighElf,"Eataine Excelsiors","Endycurus","47","71") );
    newSched_B.addTeam( new team(Slann,"Leaps of Faith","Warpstone","22","324") );
    newSched_B.addTeam( new team(Necromantic,"Full Death Metal Jacket","VampireLogan","93","210") );
    newSched_B.addTeam( new team(DarkElf,"Storm Crows","Ocrumsprug","74","226") );


    num_teams_b = newSched_B.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams_b)+" teams."  << endl;

    newSched_B.generate();


    // C-League Season 17
    schedule newSched_C(games);
    newSched_C = schedule(games);


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
    newSched_C.addTeam( new team(Undead,"UnknownTeam2","Dylanator","19","500") );
    newSched_C.addTeam( new team(Chaos,"bringers of pain","1000 Deaths","105","428") );
    newSched_C.addTeam( new team(Human,"Reavers go West","Pythrr","114","439") );
    newSched_C.addTeam( new team(Undead,"Boneyard Brutes","Khysanth","115","433") );
    newSched_C.addTeam( new team(Orc,"Rangoon Typhoon","MacPhee","51","435") );
    newSched_C.addTeam( new team(HighElf,"Sizzlin' Spirals","Badcuz","112","500") );
    newSched_C.addTeam( new team(ChaosPact,"The Expendables","Darkangeldave","48","437") );
    newSched_C.addTeam( new team(Amazon,"Titty Twister","UrukHai","97","436") );

    num_teams_c = newSched_C.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams_c)+" teams."  << endl;
    newSched_C.generate();

    // Minor Season 17
    schedule newSched_M(5);
    newSched_M = schedule(5);


    newSched_M.addTeam( new team(Khemri,"Old Kingdom Pharaohs","Gimli","31","386") );
    newSched_M.addTeam( new team(ChaosPact,"Null Zone all Blanks","Endycurus","47","394") );
    newSched_M.addTeam( new team(Halfling,"Puggy's Revenge","Majyk","92","383") );
    newSched_M.addTeam( new team(Goblin,"Star Player Killerz","Mr. Bloodwiser","91","391") );
    newSched_M.addTeam( new team(Chaos,"Demon Legion","Sallacious","15","402") );
    newSched_M.addTeam( new team(Goblin,"Villainous Kaba","Ocrumsprug","74","252") );
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
