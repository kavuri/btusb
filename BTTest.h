#ifndef BTTEST_H
#define BTTEST_H

#include <QObject>
#include <QtDBus>

class BTTest : public QObject
{
    Q_OBJECT
public:
    explicit BTTest(QObject *parent = 0);
    
    quint32 addServiceRecord ();
    
    void removeServiceRecord (quint32 recordHandle);

private:
    
    quint32         mRecordHandle;
};

#endif // BTTEST_H
