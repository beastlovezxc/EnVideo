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
    } else {
        m_bCameraOn = false;
        m_strVideoStatus = "本地录像";
    }
    m_pEvVideoCapture->restartProcess(m_bCameraOn);
    emit videoStatusChanged();
}
