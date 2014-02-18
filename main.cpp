
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

    schedule newSched(10);
    newSched.addTeam( new team(Skaven,"Death Runs Faster","Gollumullog") );
    newSched.addTeam( new team(DarkElf,"Queens of the Rampage","Gustav (Dave W.)") );
    newSched.addTeam( new team(HighElf,"Disposable Heroes","Spaceman Spiff (Lee)" ));
    newSched.addTeam( new team(WoodElf,"Heartwood Harlequins","MacPhee (Mike MacPhee)"));
    newSched.addTeam( new team(DarkElf,"Storm Crows","Ocrumsprug (Shawn W.)" ));
    newSched.addTeam( new team(Elf,"Loreal Arrowettes","General Jason (Craig)"));
    newSched.addTeam( new team(HighElf,"Ulthuan Lords","Poundfist (Mike McAree)" ));
    newSched.addTeam( new team(DarkElf,"Dark Side of the Faerie","Darkangeldave (Dave O.)"));
    newSched.addTeam( new team(Norse,"Ravers Re-Booted","dva13 (Duncan)" ));
    newSched.addTeam( new team(WoodElf,"Druid's Dream","Gazgul (Mike L.)"));
    newSched.addTeam( new team(ChaosDwarf,"The Breakfast Club ","Kodeack (Brent)" ));
    newSched.addTeam( new team(Chaos,"Popcorn Fools","Osirus11 (Ryder)"));
    newSched.addTeam( new team(Dwarf,"Half Pints","Squirrel (Mark)" ));
    newSched.addTeam( new team(ChaosDwarf,"40 Grinders","Blammaham (Steve)"));
    newSched.addTeam( new team(Human,"Harshmellow Darkstars ","Smallpox (James)" ));
    newSched.addTeam( new team(Dwarf,"Bad News Beards","Bear (Geoff)"));
    newSched.addTeam( new team(Khemri,"Bonerattle ","Fidius (Bill)" ));
    newSched.addTeam( new team(ChaosDwarf,"Hashuts Hellfires ","Wedge22 (Kristian)"));
//    newSched.addTeam( new team(Human,"Chippendales ","Edwad (Ed)" ));
//    newSched.addTeam( new team(Human,"Hogan's Heroes ","Redman (Tony)"));

    return newSched.generate();
}

