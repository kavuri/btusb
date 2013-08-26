#include <QCoreApplication>

#include "USBConnector.h"
#include "BTTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
    USBConnector usb;

    usb.openUSB ();
    */
    
    BTTest bttest;
    quint32 id = bttest.addServiceRecord ();
    
    bttest.removeServiceRecord (id);

    return a.exec();
}
