#include "USBConnector.h"

#include <QDebug>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <termios.h>

USBConnector::USBConnector(QObject *parent) :
    QObject(parent), mReadNotifier (NULL), mFd (-1)
{
}

USBConnector::~USBConnector ()
{
}

bool
USBConnector::openUSB ()
{
    const QString USB_DEVICE ("/dev/ttyGS1");

    struct termios options;
    int arg;
    long flags;

    if(isFdValid()) {
        qDebug () << "FD already open" << mFd;
        return false;
    }

    int fd = open (USB_DEVICE.toLocal8Bit ().constData (), O_RDWR | O_NOCTTY);
    if (fd < 0) {
        qDebug () <<  "Could not open file";
        return false;
    }

    flags = fcntl (fd, F_GETFL);
    fcntl (fd, F_SETFL, flags & ~O_NONBLOCK);

    tcgetattr (fd, &options);
    cfmakeraw (&options);
    options.c_oflag &= ~ONLCR;
    tcsetattr (fd, TCSANOW, &options);

    arg = fcntl (fd, F_GETFL);
    if (arg < 0) {
        qDebug () << "Not able to get file attributes";
        close (fd);
        return false;
    }

    arg |= O_NONBLOCK;
    if (fcntl (fd, F_SETFL, arg) < 0) {
        qDebug () << "Unable to set file attributes";
        close (fd);
        return false;
    }

    mFd = fd;

    qDebug () << "Successfully opened device " << USB_DEVICE << " with fd " << mFd;

    // Create a QSocketNotifier to handle the incoming data
    mReadNotifier = new QSocketNotifier (mFd, QSocketNotifier::Read, this);
    mReadNotifier->setEnabled (true);

    connect (mReadNotifier, SIGNAL (activated (int)),
             this, SLOT (socketActivated (int)));
    return true;
}


void
USBConnector::socketActivated (int fd)
{
    qDebug () << "Read socket activated with fd" << fd;
    emit dataReady (fd);
}

bool
USBConnector::isFdValid ()
{
    return (mFd != -1);
}

bool
USBConnector::closeUSB ()
{
    if (isFdValid ())
    {
        shutdown (mFd, SHUT_RDWR);
        close (mFd);
        mFd = -1;
        return true;
    }

    return false;
}

int
USBConnector::fd ()
{
    return mFd;
}
