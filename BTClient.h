#ifndef BTCLIENT_H
#define BTCLIENT_H

#include <QObject>
#include <QDBusVariant>

class BTClient : public QObject
{
    Q_OBJECT
public:
    BTClient(QObject* parent=0);
    
    virtual ~BTClient ();

    void connectToServer ();

protected slots:

    void btStateChanged (QString, QDBusVariant);
};

#endif // BTCLIENT_H
