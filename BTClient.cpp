#include "BTClient.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include <QDBusConnection>
#include <QVariant>
#include <QDebug>

BTClient::BTClient(QObject *parent) : QObject (parent)
{
    QDBusConnection bus = QDBusConnection::systemBus ();
    bool success = bus.connect ("org.bluez", "", "org.bluez.Adapter", "PropertyChanged", this, SLOT (btStateChanged (QString, QDBusVariant)));
    qDebug () << success;
    if (success == false)
        qWarning("Cannot connect to org.bluez.Adapter::PropertyChanged signal.");
}

BTClient::~BTClient ()
{
}

void
BTClient::connectToServer ()
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    //char dest[18] = "00:02:72:B0:00:26";
    char dest[18] = "00:1F:81:00:08:30";

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 25;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    //status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    // send a message
    if( status == 0 ) {
        status = write(s, "hello!", 6);
    }

    if( status < 0 ) perror("uh oh");

    close(s);
}

void
BTClient::btStateChanged (QString key, QDBusVariant value)
{
    QVariant v = value.variant ();
    qDebug () << "Property:" << key << " changed to " << v.toString ();
}
