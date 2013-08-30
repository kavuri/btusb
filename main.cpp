#include <QCoreApplication>

#include "USBConnector.h"
#include "BTTest.h"
#include <QString>
#include <QDebug>
#include "BTServer.h"
#include "BTClient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
    USBConnector usb;

    usb.openUSB ();
    */
    
    QString cmd (argv[1]);
    if (cmd == "s")
    {
        qDebug () << "Starting bt server...";
        BTServer server;
        server.startListen ();
    } else
    {
        BTClient client;
        client.connectToServer ();
    }

    //quint32 id = bttest.addServiceRecord ();
    //bttest.removeServiceRecord (id);

    return 0;
}
