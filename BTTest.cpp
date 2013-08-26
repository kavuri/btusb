#include "BTTest.h"

#include <QDebug>
#include <QFile>
#include <QtDBus>

BTTest::BTTest(QObject *parent) :
    QObject(parent)
{
}

quint32
BTTest::addServiceRecord ()
{
    // Initialize dbus
    QDBusInterface mgrIface ("org.bluez", "/", "org.bluez.Manager", QDBusConnection::systemBus ());
    if (!mgrIface.isValid ())
    {
        qDebug () << "Unable to initialize bluez manager interface";
        return -1;
    }
    
    QDBusReply<QDBusObjectPath> reply = mgrIface.call (QLatin1String ("DefaultAdapter"));
    if (!reply.isValid ())
    {
        qDebug () << "Default adapter path not found";
        return -1;
    }
    
    QString defaultAdapterPath = reply.value ().path ();
    
    qDebug () << "Path:" << defaultAdapterPath;
    
    QDBusInterface serviceIface ("org.bluez", defaultAdapterPath, "org.bluez.Service", QDBusConnection::systemBus() );
    
    if(!serviceIface.isValid ())
    {
        qDebug () << "Could not find service interface: " << serviceIface.lastError ();
        return -1;
    }
    
    // Read service record file
    QFile file ("syncml_server_sdp_record.xml");
    if (!file.open (QIODevice::ReadOnly))
    {
        qDebug () << "Service record file does not exist";
        return -1;
    }
    QByteArray sdpRecord = file.readAll ();
    file.close ();
    
    QDBusReply<unsigned int> addResponse = serviceIface.call (QLatin1String ("AddRecord"), QLatin1String (sdpRecord));
    
    if( !addResponse.isValid() )
    {
        qDebug () <<  "Could not add service record";
        return -1;
    }

    qDebug () <<  "Service record successfully added with handle " << addResponse.value ();
    return addResponse.value ();
}

void
BTTest::removeServiceRecord (quint32 recordHandle)
{
}
