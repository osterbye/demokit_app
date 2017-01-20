#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pubnubreceiver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_receiver = new PubNubReceiver(this);
    connect(m_receiver, SIGNAL(newVehicleStatus(QStringList)), this, SLOT(vehicleStatus(QStringList)));
    connect(m_receiver, SIGNAL(newstatusDoorFL(bool)), this, SLOT(statusDoorFL(bool)));
    connect(m_receiver, SIGNAL(newstatusDoorFR(bool)), this, SLOT(statusDoorFR(bool)));
    connect(m_receiver, SIGNAL(newstatusDoorRL(bool)), this, SLOT(statusDoorRL(bool)));
    connect(m_receiver, SIGNAL(newstatusDoorRR(bool)), this, SLOT(statusDoorRR(bool)));
    connect(m_receiver, SIGNAL(newstatusSeatFL(bool)), this, SLOT(statusSeatFL(bool)));
    connect(m_receiver, SIGNAL(newstatusSeatFR(bool)), this, SLOT(statusSeatFR(bool)));
    connect(m_receiver, SIGNAL(newstatusSeatRL(bool)), this, SLOT(statusSeatRL(bool)));
    connect(m_receiver, SIGNAL(newstatusSeatRR(bool)), this, SLOT(statusSeatRR(bool)));
    connect(m_receiver, SIGNAL(newstatusLocked(bool)), this, SLOT(statusLocked(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::vehicleStatus(QStringList status)
{
    for (int i = 0; i < status.count(); ++i) {
        ui->textBrowser->append(status.at(i));
    }

    ui->textBrowser->append("\n\n");
}

void MainWindow::statusLocked(bool locked)
{
    if (locked) {
        ui->labelLockStatus->setPixmap(QPixmap(":/images/icon_locked.png"));
    } else {
        ui->labelLockStatus->setPixmap(QPixmap(":/images/icon_unlocked.png"));
    }
}

void MainWindow::statusDoorFL(bool open)
{
    if (open) {
        ui->labelDoorFL->setPixmap(QPixmap(":/images/door_open.png"));
    } else {
        ui->labelDoorFL->setPixmap(QPixmap(":/images/door_closed.png"));
    }
}

void MainWindow::statusDoorFR(bool open)
{
    if (open) {
        ui->labelDoorFR->setPixmap(QPixmap(":/images/door_open.png"));
    } else {
        ui->labelDoorFR->setPixmap(QPixmap(":/images/door_closed.png"));
    }
}

void MainWindow::statusDoorRL(bool open){
    if (open) {
        ui->labelDoorRL->setPixmap(QPixmap(":/images/door_open.png"));
    } else {
        ui->labelDoorRL->setPixmap(QPixmap(":/images/door_closed.png"));
    }
}

void MainWindow::statusDoorRR(bool open)
{
    if (open) {
        ui->labelDoorRR->setPixmap(QPixmap(":/images/door_open.png"));
    } else {
        ui->labelDoorRR->setPixmap(QPixmap(":/images/door_closed.png"));
    }
}

void MainWindow::statusSeatFL(bool occupied)
{
    if (occupied) {
        ui->labelSeatFL->setPixmap(QPixmap(":/images/seat_occupied.png"));
    } else {
        ui->labelSeatFL->setPixmap(QPixmap(":/images/seat_unoccupied.png"));
    }
}

void MainWindow::statusSeatFR(bool occupied)
{
    if (occupied) {
        ui->labelSeatRL->setPixmap(QPixmap(":/images/seat_occupied.png"));
    } else {
        ui->labelSeatFR->setPixmap(QPixmap(":/images/seat_unoccupied.png"));
    }
}

void MainWindow::statusSeatRL(bool occupied)
{
    if (occupied) {
        ui->labelSeatRL->setPixmap(QPixmap(":/images/seat_occupied.png"));
    } else {
        ui->labelSeatRL->setPixmap(QPixmap(":/images/seat_unoccupied.png"));
    }
}

void MainWindow::statusSeatRR(bool occupied)
{
    if (occupied) {
        ui->labelSeatRR->setPixmap(QPixmap(":/images/seat_occupied.png"));
    } else {
        ui->labelSeatRR->setPixmap(QPixmap(":/images/seat_unoccupied.png"));
    }
}

void MainWindow::on_pushButtonUnlock_clicked()
{
    m_receiver->vehicleLockRequest(false);
}

void MainWindow::on_pushButtonLock_clicked()
{
    m_receiver->vehicleLockRequest(true);
}
