
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
    schedule newSched(5);
    for (int games=5;games<=15;games++ ){
        for (int num_tm=1;num_tm<=30;num_tm++ ){

            out << QString("*************") << endl;
            out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_tm)+" teams."  << endl;
            newSched = schedule(games);
            if (num_tm>0) newSched.addTeam( new team(Skaven,"Death Runs Faster","Gollumullog") );
            if (num_tm>1) newSched.addTeam( new team(DarkElf,"Queens of the Rampage","Gustav (Dave W.)") );
            if (num_tm>2) newSched.addTeam( new team(HighElf,"Disposable Heroes","Spaceman Spiff (Lee)" ));
            if (num_tm>3) newSched.addTeam( new team(WoodElf,"Heartwood Harlequins","MacPhee (Mike MacPhee)"));
            if (num_tm>4) newSched.addTeam( new team(DarkElf,"Storm Crows","Ocrumsprug (Shawn W.)" ));
            if (num_tm>5) newSched.addTeam( new team(Elf,"Loreal Arrowettes","General Jason (Craig)"));
            if (num_tm>6) newSched.addTeam( new team(HighElf,"Ulthuan Lords","Poundfist (Mike McAree)" ));
            if (num_tm>7) newSched.addTeam( new team(DarkElf,"Dark Side of the Faerie","Darkangeldave (Dave O.)"));
            if (num_tm>8) newSched.addTeam( new team(Norse,"Ravers Re-Booted","dva13 (Duncan)" ));
            if (num_tm>9) newSched.addTeam( new team(WoodElf,"Druid's Dream","Gazgul (Mike L.)"));
            if (num_tm>10) newSched.addTeam( new team(ChaosDwarf,"The Breakfast Club ","Kodeack (Brent)" ));
            if (num_tm>11) newSched.addTeam( new team(Chaos,"Popcorn Fools","Osirus11 (Ryder)"));
            if (num_tm>12) newSched.addTeam( new team(Dwarf,"Half Pints","Squirrel (Mark)" ));
            if (num_tm>13) newSched.addTeam( new team(ChaosDwarf,"40 Grinders","Blammaham (Steve)"));
            if (num_tm>14) newSched.addTeam( new team(Human,"Harshmellow Darkstars ","Smallpox (James)" ));
            if (num_tm>15) newSched.addTeam( new team(Dwarf,"Bad News Beards","Bear (Geoff)"));
            if (num_tm>16) newSched.addTeam( new team(Khemri,"Bonerattle ","Fidius (Bill)" ));
            if (num_tm>17) newSched.addTeam( new team(ChaosDwarf,"Hashuts Hellfires ","Wedge22 (Kristian)"));
            if (num_tm>18) newSched.addTeam( new team(Human,"Chippendales ","Edwad (Ed)" ));
            if (num_tm>19) newSched.addTeam( new team(Human,"Hogan's Heroes ","Redman (Tony)"));

            if (num_tm>20) newSched.addTeam( new team(ChaosDwarf,"Team 21","Kodeack (Brent)" ));
            if (num_tm>21) newSched.addTeam( new team(Chaos,"Team 22 Fools","Osirus11 (Ryder)"));
            if (num_tm>22) newSched.addTeam( new team(Dwarf,"Team 23 Pints","Squirrel (Mark)" ));
            if (num_tm>23) newSched.addTeam( new team(ChaosDwarf,"Team 24 Grinders","Blammaham (Steve)"));
            if (num_tm>24) newSched.addTeam( new team(Human,"Team 25 Darkstars ","Smallpox (James)" ));
            if (num_tm>25) newSched.addTeam( new team(Dwarf,"Team 26 Beards","Bear (Geoff)"));
            if (num_tm>26) newSched.addTeam( new team(Khemri,"Team 27 ","Fidius (Bill)" ));
            if (num_tm>27) newSched.addTeam( new team(ChaosDwarf,"Team 28 Hellfires ","Wedge22 (Kristian)"));
            if (num_tm>28) newSched.addTeam( new team(Human,"Team 29 ","Edwad (Ed)" ));
            if (num_tm>29) newSched.addTeam( new team(Human,"Team 30 Heroes ","Redman (Tony)"));
            newSched.generate();
        }
    }
    return 0;
}

