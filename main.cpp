
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

// Season18 10 "D://project//thunder_noui//18_b//"
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

    if (arguments.count() == 2){
        // this section reads an html file and extracts all the teams
        QFile file(QString(arguments.at(1)));
        if (!file.open(QIODevice::ReadOnly)) {
           //("Unable to open file %s, aborting\n", file.fileName().toStdString().c_str());
           return 1;
        }
        if (!file.isReadable()) {
            //("Unable to read file %s, aborting\n", file.fileName().toStdString().c_str());
            return false;
        }

        // B-League Schedule
        int games = 10;
        QString baseFileName = "D://project//thunder_noui//output//season19//1//";
        QString filename = baseFileName + "thundersched_19_B.txt";
        schedule newSched_B(filename, games);
        newSched_B = schedule(filename, games);

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QRegularExpression team_html(".*<td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=2\\&amp;obj_id=(\\d+)'>([\\w-']+)</a></td><td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=3\\&amp;obj_id=(\\d+)'>([\\w-']+)</a></td>.*<td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=4\\&amp;obj_id=(\\d+)'>([\\w-']+)</a></td>.*$");
            QRegularExpressionMatch match = team_html.match(line);
            if(match.hasMatch()){
                QString team_id = match.captured(1);
                QString name = match.captured(2);
                QString coach_id = match.captured(3);
                QString coach = match.captured(4);
                QString race = match.captured(6);
                int race_id = getMyTeam(race);
                team* add_team = new team( race_id
                                        , name
                                        , coach
                                        , coach_id
                                        , team_id );
                newSched_B.addTeam( add_team );
            }
        }
        int num_teams_b = newSched_B.numberTeams();

        out << QString("*************") << endl;
        out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams_b)+" teams."  << endl;

        newSched_B.generate();
    }


    if (arguments.count() < 4){
        return 1;
    }

    // import teams
    int games = arguments.at(2).toInt();
    QString in_file = arguments.at(3)+"teams.txt";
    QString out_file = arguments.at(3)+ arguments.at(1) + ".txt";

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
