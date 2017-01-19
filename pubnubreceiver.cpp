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
    jsonObj.insert("App connected", "Spiri e-up reader");
    m_handler->sendMessage(m_channelName, QJsonDocument(jsonObj));
}

void PubNubReceiver::PubNubReceive(QString channel, QStringList messages)
{
    qDebug() << "\n-----------\n";
    qDebug() << "Channel: " << channel << "\nMessages:\n" << messages << "\n";
    qDebug() << "\n...........\n";

    //emit newVehicleStatus(messages);

    //PN_DBG("subscribe parsing");
    //QList<QString> msg = d_pb_subscribe->get_all();
    //for (int i = 0; i < msg.size(); ++i) {
    for (int i = 0; i < messages.size(); ++i) {
        //PN_DBG("subscribe message " + msg[i] + '\n');
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
        emit statusLocked((status == valTrue));

        status = object.value(":doorOpenFL");
        emit statusDoorFL((status == valTrue));
        status = object.value(":doorOpenFR");
        emit statusDoorFR((status == valTrue));
        status = object.value(":doorOpenRL");
        emit statusDoorRL((status == valTrue));
        status = object.value(":doorOpenRR");
        emit statusDoorRR((status == valTrue));

        // Occupied status is actually unoccupied status, so act in inverse
        status = object.value(":seatOccupiedFL");
        emit statusSeatFL((status == valFalse));
        status = object.value(":seatOccupiedFR");
        emit statusSeatFR((status == valFalse));
        status = object.value(":seatOccupiedRL");
        emit statusSeatRL((status == valFalse));
        status = object.value(":seatOccupiedRR");
        emit statusSeatRR((status == valFalse));


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
