#include <QCoreApplication>
#include <QStringList>
#include <QString>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "team.h"
#include "game.h"
#include "schedule.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , _current_sched(NULL)
  , _num_games(0)
{
    ui->setupUi(this);
    connect(ui->numGames_spinBox, SIGNAL(editingFinished()), this, SLOT(slot_set_games()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slot_generate()
{
    if (_current_sched != NULL)
        _current_sched->generate();
    show();
}

void MainWindow::slot_new_sched()
{
    _current_sched = new schedule(_num_games);
    show();
}

void MainWindow::slot_set_games()
{
    _num_games = ui->numGames_spinBox->value();
    if (_current_sched != NULL)
        _current_sched->numGames(ui->numGames_spinBox->value());
    show();
}
