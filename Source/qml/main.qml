import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5

import "../Component"
Item {
    visible: true
    width: 800
    height: 480

    Image {
        id: evShowFrame
        cache: false
        anchors.top: parent.top
        anchors.left: parent.left
        width: 600
        height: 480
    }
    Connections {
        target: EvVideoCaptureView
        onFrameChanged: {
            evShowFrame.source="";
            evShowFrame.source="image://img";
        }
    }
    Button {
        id: videoBtn
        text: EvSettingView.videoStatus
        anchors.right: parent.right
        anchors.rightMargin: 80
        anchors.verticalCenter: parent.verticalCenter
        highlighted: true
        flat: true
        onClicked: {
            setVideoBtn()
        }
    }

    function setVideoBtn() {
        if(EvSettingView.cameraOn)
            EvSettingView.cameraOn = false;
        else
            EvSettingView.cameraOn = true;
    }

}
