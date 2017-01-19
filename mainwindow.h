#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PubNubReceiver;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void vehicleStatus(QStringList status);
    void statusLocked(bool locked);
    void statusDoorFL(bool open);
    void statusDoorFR(bool open);
    void statusDoorRL(bool open);
    void statusDoorRR(bool open);
    void statusSeatFL(bool occupied);
    void statusSeatFR(bool occupied);
    void statusSeatRL(bool occupied);
    void statusSeatRR(bool occupied);

private:
    Ui::MainWindow *ui;

    PubNubReceiver *m_receiver;
};

#endif // MAINWINDOW_H
