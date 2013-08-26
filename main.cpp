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
    bttest.addServiceRecord ();

    return a.exec();
}
