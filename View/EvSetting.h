#ifndef EVSETTING_H
#define EVSETTING_H

#include <QObject>
#include "Common/EvVideoCapture.h"
class EvSetting : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString videoStatus READ getVideoStatus NOTIFY videoStatusChanged)
    Q_PROPERTY(bool cameraOn READ getCameraOn WRITE setCameraOn)
    Q_PROPERTY(QString videoPath READ getVideoPath WRITE setVideoPath NOTIFY videoPathChanged)

public:
    EvSetting();


    void registVideoCapture(EvVideoCapture* evVideoCapture);

    void setCameraOn(bool isOn);
    void setVideoPath(QString videoPath);
    QString getVideoStatus() { return m_strVideoStatus;}
    QString getVideoPath() { return m_strVideoPath;}
    bool getCameraOn() { return m_bCameraOn;}

signals:
    void videoStatusChanged();
    void videoPathChanged();
private:
    QString m_strVideoStatus;
    QString m_strVideoPath;
    bool m_bCameraOn;

    EvVideoCapture* m_pEvVideoCapture;
};

#endif // EVSETTING_H
