#ifndef EVSETTING_H
#define EVSETTING_H

#include <QObject>
#include "Common/EvVideoCapture.h"
class EvSetting : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString videoStatus READ getVideoStatus NOTIFY videoStatusChanged)
    Q_PROPERTY(bool cameraOn READ getCameraOn WRITE setCameraOn)

public:
    EvSetting();


    void registVideoCapture(EvVideoCapture* evVideoCapture);

    void setCameraOn(bool isOn);
    QString getVideoStatus() { return m_strVideoStatus;}
    bool getCameraOn() { return m_bCameraOn;}

signals:
    void videoStatusChanged();
private:
    QString m_strVideoStatus;
    bool m_bCameraOn;

    EvVideoCapture* m_pEvVideoCapture;
};

#endif // EVSETTING_H
