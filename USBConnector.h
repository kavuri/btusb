#ifndef USBCONNECTOR_H
#define USBCONNECTOR_H

#include <QObject>

#include <QSocketNotifier>

class USBConnector : public QObject
{
    Q_OBJECT
public:
    explicit USBConnector (QObject *parent = 0);

    virtual ~USBConnector ();

    bool openUSB ();

    bool closeUSB ();

    int fd ();

signals:

    void dataReady (int fd);

    void socketClosed (int fd);

protected slots:

    void socketActivated (int fd);

private:

    bool isFdValid ();

    QSocketNotifier *mReadNotifier;

    int mFd;
};

#endif // USBCONNECTOR_H
