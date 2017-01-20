#include "pubnubreceiver.h"
#include "pubnubhandler.h"
#include <QDebug>
#include <QJsonObject>

PubNubReceiver::PubNubReceiver(QObject *parent) : PubNubSubscriber(parent)
{
    qDebug() << "Setting up PubNub\n----------\n";
    m_handler = new PubNubHandler("pub-c-38db667a-fc13-4740-bbfc-c2a9298c1b22",
                                  "sub-c-edf80ad4-912f-11e6-bb6b-0619f8945a4f",
                                  this);

    m_channelName = "vehicle_status";

    m_handler->subscribe(m_channelName, this);

    QJsonObject jsonObj;
    jsonObj.insert("App connected", "Spiri demo kit");
    m_handler->sendMessage(m_channelName, QJsonDocument(jsonObj));
}

void PubNubReceiver::PubNubReceive(QString channel, QStringList messages)
{
    qDebug() << "\n-----------\n";
    qDebug() << "Channel: " << channel << "\nMessages:\n" << messages << "\n";
    qDebug() << "\n...........\n";

    emit newVehicleStatus(messages);

    //PN_DBG("subscribe parsing");
    //QList<QString> msg = d_pb_subscribe->get_all();
    //for (int i = 0; i < msg.size(); ++i) {
    qDebug() << "number of messages: " << messages.size();
    for (int i = 0; i < messages.size(); ++i) {
        qDebug() << "subscribe message " + messages[i];
        QJsonValue valTrue("true");
        QJsonValue valFalse("false");

        /*QJsonValue doorOpenFL(":doorOpenFL");
        QJsonValue doorOpenFR(":doorOpenFR");
        QJsonValue doorOpenRL(":doorOpenRL");
        QJsonValue doorOpenRR(":doorOpenRR");
        QJsonValue seatOccupiedFL(":seatOccupiedFL");
        QJsonValue seatOccupiedFR(":seatOccupiedFR");
        QJsonValue seatOccupiedRL(":seatOccupiedRL");
        QJsonValue seatOccupiedRR(":seatOccupiedRR");
        QJsonValue vehicleLocked(":vehicleLocked");*/

        QJsonDocument json = QJsonDocument::fromJson(messages[i].toUtf8());
        QJsonObject object = json.object();

        QJsonValue status = object.value(":vehicleLocked");
        if (!(status == QJsonValue::Undefined))
            emit newstatusLocked((status == valTrue));

        status = object.value(":doorOpenFL");
        if (!(status == QJsonValue::Undefined))
            emit newstatusDoorFL((status == valTrue));
        status = object.value(":doorOpenFR");
        if (!(status == QJsonValue::Undefined))
            emit newstatusDoorFR((status == valTrue));
        status = object.value(":doorOpenRL");
        if (!(status == QJsonValue::Undefined))
            emit newstatusDoorRL((status == valTrue));
        status = object.value(":doorOpenRR");
        if (!(status == QJsonValue::Undefined))
            emit newstatusDoorRR((status == valTrue));

        // Occupied status is actually unoccupied status, so act in inverse
        status = object.value(":seatOccupiedFL");
        if (!(status == QJsonValue::Undefined))
            emit newstatusSeatFL((status == valFalse));
        status = object.value(":seatOccupiedFR");
        if (!(status == QJsonValue::Undefined))
            emit newstatusSeatFR((status == valFalse));
        status = object.value(":seatOccupiedRL");
        if (!(status == QJsonValue::Undefined))
            emit newstatusSeatRL((status == valFalse));
        status = object.value(":seatOccupiedRR");
        if (!(status == QJsonValue::Undefined))
            emit newstatusSeatRR((status == valFalse));


        /*QJsonValue cmd = object.value("doorlock");
        if (cmd == cmdLock) {
            emit cmdRequestDoorLock(true);
            //PN_DBG("LOCK THE DOOR");
        } else if (cmd == cmdUnlock) {
            emit cmdRequestDoorLock(false);
            //PN_DBG("UNLOCK THE DOOR");
        }*/
    }
}

void PubNubReceiver::vehicleLockRequest(bool lock)
{
    QJsonObject jsonObj;
    // Requests are acted on inversed, so we send unlock request in order to lock vehicle
    if (lock) {
        jsonObj.insert("doorlock", "unlock");
    } else {
        jsonObj.insert("doorlock", "lock");
    }
    m_handler->sendMessage("vehicle_cmd", QJsonDocument(jsonObj));
}
