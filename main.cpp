#include <QCoreApplication>

#include "USBConnector.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    USBConnector usb;

    usb.enable ();

    return a.exec();
}
