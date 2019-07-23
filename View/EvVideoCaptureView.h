#ifndef EVVIDEOCAPTUREVIEW_H
#define EVVIDEOCAPTUREVIEW_H

#include <QObject>
class EvVideoCaptureView : public QObject
{
    Q_OBJECT
public:
    EvVideoCaptureView();

public slots:
    void setFrame();

signals:
    void frameChanged();
};

#endif // EVVIDEOCAPTUREVIEW_H
