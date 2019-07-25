#include "EvSetting.h"

EvSetting::EvSetting()
{
    m_bCameraOn = false;
    m_strVideoStatus = "本地录像";
}

void EvSetting::registVideoCapture(EvVideoCapture *evVideoCapture)
{
    m_pEvVideoCapture = evVideoCapture;
}

void EvSetting::setCameraOn(bool isOn)
{
    if(isOn) {
        m_bCameraOn = true;
        m_strVideoStatus = "摄像头录像";
        m_pEvVideoCapture->setCameraOn(m_bCameraOn);
        m_pEvVideoCapture->closeProcess();
        m_pEvVideoCapture->startVideoCaptureProcess();
    } else {
        m_bCameraOn = false;
        m_pEvVideoCapture->setCameraOn(m_bCameraOn);
        m_strVideoStatus = "本地录像";
        m_pEvVideoCapture->closeProcess();
    }
    emit videoStatusChanged();
}

void EvSetting::setVideoPath(QString videoPath)
{
    m_strVideoPath = videoPath;
    m_pEvVideoCapture->setVideoPath(m_strVideoPath);
    m_pEvVideoCapture->startVideoCaptureProcess();
}
