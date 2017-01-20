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
    void newstatusLocked(bool locked);
    void newstatusDoorFL(bool open);
    void newstatusDoorFR(bool open);
    void newstatusDoorRL(bool open);
    void newstatusDoorRR(bool open);
    void newstatusSeatFL(bool occupied);
    void newstatusSeatFR(bool occupied);
    void newstatusSeatRL(bool occupied);
    void newstatusSeatRR(bool occupied);

private:
    PubNubHandler *m_handler;
    QString m_channelName;
};

#endif // PUBNUBRECEIVER_H
