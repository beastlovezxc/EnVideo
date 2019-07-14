#include "EvDispatcher.h"

EvDispatcher::EvDispatcher()
{
    this->moveToThread(&mWorkThread);
    connect(&mWorkThread, SIGNAL(started()), this, SLOT(slotDispatcherProcess()), Qt::QueuedConnection);
}

EvDispatcher::~EvDispatcher() {

}

void EvDispatcher::dispatcherThreadStart() {
    mWorkThread.start();
}

void EvDispatcher::slotDispatcherProcess() {

}
