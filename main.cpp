
#include <QCoreApplication>
#include <QStringList>
#include <QString>
#include <QTextStream>
#include <QtSql>
#include <QRegExp>


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

    QStringList arguments = a.arguments();

    if (arguments.count() < 4){
        return 1;
    }

    // import teams
    int games = arguments.at(2).toInt();
    QString file_base = "D:\\project\\thunder_noui\\files\\";
    QString in_file = file_base+arguments.at(3)+"teams.txt";
    QString out_file = file_base+arguments.at(3)+ arguments.at(1) + ".txt";

    schedule newSched(out_file, games);
    int num_teams = 0;

    QFile file(in_file);
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while (!in.atEnd()){
            QString line = in.readLine();
            QRegExp comment_RexExp("^\\s*//.*");
            QRegExp team_RexExp("^\\s*([\\w]+),(.*),(.*),(\\d+),(\\d+)\\s*$");
            if (comment_RexExp.exactMatch(line)){ continue;}
            if (team_RexExp.exactMatch(line)){
                QStringList team_values = team_RexExp.capturedTexts();
                team* add_team = new team( getMyTeam(team_values.at(1))
                                        , team_values.at(2)
                                        , team_values.at(3)
                                        , team_values.at(4)
                                        , team_values.at(5) );
                newSched.addTeam( add_team );
            }
        }
        file.close();
    }

    num_teams = newSched.numberTeams();

    out << QString("*************") << endl;
    out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams)+" teams."  << endl;

    newSched.generate();

    return 0;
}
