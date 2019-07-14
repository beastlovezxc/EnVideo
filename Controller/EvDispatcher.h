#ifndef EVDISPATCHER_H
#define EVDISPATCHER_H

#include <QObject>
#include <QThread>
class EvDispatcher : public QObject
{
    Q_OBJECT
public:
    EvDispatcher();
    ~EvDispatcher();
    void dispatcherThreadStart();

    QThread mWorkThread;


public slots:
    void slotDispatcherProcess();
};

#endif // EVDISPATCHER_H
