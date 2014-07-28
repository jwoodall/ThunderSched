
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
  /*
    schedule newSched_B(games);
    newSched_B = schedule(games);


    // B -League Season 17
    newSched_B.addTeam( new team(ChaosDwarf,"Apocalypto","J.Mac") );
    newSched_B.addTeam( new team(Lizardmen,"Serpentine glory","Murray") );
    newSched_B.addTeam( new team(Chaos,"Freaks and Weirdos","Lee") );
    newSched_B.addTeam( new team(Dwarf,"Bad News Beards","Geoff") );
    newSched_B.addTeam( new team(Necromantic,"FDMJ","Dan C") );
    newSched_B.addTeam( new team(Human,"Verde Slackers","James M.") );
    newSched_B.addTeam( new team(Slann,"Freezing Reign","Greg F.") );
    newSched_B.addTeam( new team(Orc,"Waauugghh Mash'een ","Ian S") );
    newSched_B.addTeam( new team(Orc,"Angmar Express","Dave W") );
    newSched_B.addTeam( new team(Norse,"F'N Givers ","Tyler") );
    newSched_B.addTeam( new team(ChaosDwarf,"40Grinders ","Steve") );
    newSched_B.addTeam( new team(Chaos,"Popcorn Fools ","Ryder") );
    newSched_B.addTeam( new team(ChaosDwarf,"Hashut's Hellfires","Kristian") );
    newSched_B.addTeam( new team(ChaosDwarf,"Phelegraen Marauders","Jason W") );
    newSched_B.addTeam( new team(HighElf,"Eataine Excelsiors","Jon") );
    newSched_B.addTeam( new team(Slann,"Leaps of Faith","Kavin") );


    num_teams_b = newSched_B.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams_b)+" teams."  << endl;

    newSched_B.generate();
*/
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
    newSched_C.addTeam( new team(DarkElf,"Niriak Yellowjakets ","Bubbles","9","431") );
    newSched_C.addTeam( new team(Human,"Silly English Kannniggits.","Poundfist","6","425") );
    newSched_C.addTeam( new team(Nurgle,"Newly Infected","Squirrel","103","427") );
    newSched_C.addTeam( new team(DarkElf,"Zardok Pitfighters","Cyrust59","60","500") );
    newSched_C.addTeam( new team(Undead,"UnknownTeam2","Dylanator","19","500") );
    newSched_C.addTeam( new team(Chaos,"bringers of pain","1000 Deaths","105","428") );
    newSched_C.addTeam( new team(Human,"UnknownTeam4","Pythrr","114","500") );
    newSched_C.addTeam( new team(Undead,"Boneyard Brutes","Khysanth","115","433") );
    newSched_C.addTeam( new team(Orc,"Rangoon Typhoon","MacPhee","51","500") );
    newSched_C.addTeam( new team(HighElf,"Sizzlin' Spirals","Badcuz","112","500") );
    newSched_C.addTeam( new team(ChaosPact,"UnknownTeam6","Darkangeldave","48","500") );
    newSched_C.addTeam( new team(Amazon,"Titty Twister","UrukHai","97","500") );

    num_teams_c = newSched_C.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams_c)+" teams."  << endl;
    newSched_C.generate();

/*
    // Minor Season 17
    schedule newSched_M(5);
    newSched_M = schedule(5);


    newSched_M.addTeam( new team(Khemri,"Old Kingdom Pharaohs","Murray") );
    newSched_M.addTeam( new team(ChaosPact,"Null Zone all Blanks","Jon") );
    newSched_M.addTeam( new team(Halfling,"Puggy's Revenge","Matt") );
    newSched_M.addTeam( new team(Goblin,"Star Player Killerz","Cam") );
    newSched_M.addTeam( new team(Chaos,"Demon Legion","Jesse") );
    newSched_M.addTeam( new team(Goblin,"Villainous Kaba","Shawn") );
    newSched_M.addTeam( new team(Amazon,"Odelay","Mike Adams") );
    newSched_M.addTeam( new team(Halfling,"No Expectations","Geoff") );
    newSched_M.addTeam( new team(ChaosDwarf,"Taco Bull","Ed L.") );
    newSched_M.addTeam( new team(Human,"Dm Electric","Dylan") );
    newSched_M.addTeam( new team(ChaosPact,"Powers of Pain","Ivan") );
    newSched_M.addTeam( new team(Norse,"Ravers Rebooted","Duncan") );
    newSched_M.addTeam( new team(Vampire,"Darknight Regen","Kavin") );
    newSched_M.addTeam( new team(Elf,"Rank Amateurs ","Trent") );
    newSched_M.addTeam( new team(ChaosPact,"Positive Thinking","Dan C.") );
    newSched_M.addTeam( new team(Human,"Backdoor Blitzers","Tyler") );
    newSched_M.addTeam( new team(HighElf,"Mighty High","Kristian") );
    newSched_M.addTeam( new team(HighElf,"Swiftsure Royals","Steve") );

    int num_teams_m = newSched_M.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(5)+" games, "+QString::number(num_teams_m)+" teams."  << endl;
    newSched_M.generate();
*/
    return 0;
}

