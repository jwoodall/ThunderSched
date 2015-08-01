
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

    out << "ThunderSchedule version 0.3" << endl;
    // v0.1 inital design with hand coded teams
    // v0.2 accepts files, and arguments in the form of [season] [games] [league name]
    // v0.3 creates schedule from an html dump fron the obblm database
    //      -- go to team standings, change tournament to be the selected one, right click save as website, html only
    //      -- pass that file name as the first argument, second argument is number of games


    QStringList arguments = a.arguments();

    if (arguments.count() == 3){
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
        int games = arguments.at(2).toInt();
//        QString baseFileName = "D://project//thunder_noui//output//season19//1//";
//      QString filename = baseFileName + "thundersched_19_B.txt";
        QString filename = arguments.at(1) + ".out";
        schedule newSched(filename, games);
        newSched = schedule(filename, games);

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
//            QRegularExpression team_html(".*<td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=2\\&amp;obj_id=(\\d+)'>([\\w-'\\s]+)</a></td><td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=\\d\\&amp;obj_id=(\\d+)'>([\\w-'\\s]+)</a></td>.*<td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=\\d\\&amp;obj_id=(\\d+)'>([\\w-'\\s]+)</a></td>.*$");
            QRegularExpression team_html(".*<td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=2\\&amp;obj_id=(\\d+)'>([\\x20-\\xFF]+)</a></td><td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=\\d\\&amp;obj_id=(\\d+)'>([\\x20-\\xFF]+)</a></td>.*<td><a\\shref='index\\.php\\?section=objhandler\\&amp;type=1\\&amp;obj=\\d\\&amp;obj_id=(\\d+)'>([\\x20-\\xFF]+)</a></td>.*$");
            QRegularExpressionMatch match = team_html.match(line);
            if(match.hasMatch()){
                QString team_id = match.captured(1);
                QString name = match.captured(2);
                QString coach_id = match.captured(3);
                QString coach = match.captured(4);
                QString race = match.captured(6);
                int race_id = getMyTeam(race);
                if (race_id < 0) { out << QString("Race not found:") << race << " for " << name << endl; }
                team* add_team = new team( race_id
                                        , name
                                        , coach
                                        , coach_id
                                        , team_id );
                newSched.addTeam( add_team );
            }
        }
        int num_teams = newSched.numberTeams();

        out << QString("*************") << endl;
        out << QString("Schedule for ")+QString::number(games)+" games, "+QString::number(num_teams)+" teams."  << endl;

        newSched.generate();
    }

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
            QRegExp team_RexExp("^\\s*([\\w]+)\\s*,\\s*(.*)\\s*,\\s*(.*)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*$");
            if (comment_RexExp.exactMatch(line)){ continue;}
            if (team_RexExp.exactMatch(line)){
                QStringList team_values = team_RexExp.capturedTexts();
                team* add_team = new team( getMyTeam(team_values.at(1))
                                        , team_values.at(2)
                                        , team_values.at(3)
                                        , team_values.at(4)
                                        , team_values.at(5) );
                if (getMyTeam(team_values.at(1)) < 0) { out << QString("Race not found:") << team_values.at(1) << " for " << team_values.at(2) << endl; }

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
