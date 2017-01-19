#ifndef PUBNUBRECEIVER_H
#define PUBNUBRECEIVER_H
#include "pubnubsubscriber.h"
#include <QJsonDocument>

class PubNubHandler;

class PubNubReceiver : public PubNubSubscriber
{
    Q_OBJECT
public:
    PubNubReceiver(QObject *parent = 0);

    void PubNubReceive(QString channel, QStringList messages);
    void vehicleLockRequest(bool lock);

signals:
    void newVehicleStatus(QStringList status);
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
    PubNubHandler *m_handler;
    QString m_channelName;
};

#endif // PUBNUBRECEIVER_H
