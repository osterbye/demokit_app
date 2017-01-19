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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::vehicleStatus(QStringList status)
{
    //ui->textBrowser->append(status);
    for (int i = 0; i < status.count(); ++i) {
        ui->textBrowser->append(status.at(i));
    }

    ui->textBrowser->append("\n\n");
}
