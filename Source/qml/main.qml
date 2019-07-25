import QtQuick 2.2
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3

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
        anchors.rightMargin: 50
        anchors.verticalCenter: parent.verticalCenter
        width: 100
        highlighted: true
        flat: true
        onClicked: {
            setVideoBtn()
        }
    }
    Button {
        id: fileDialogBtn
        text: qsTr("打开文件");
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: videoBtn.bottom
        anchors.topMargin: 30
        width: 100
        highlighted: true
        flat: true
        onClicked: {
            videoDialog.open()
        }
    }
    Text {
        id: videoPath
        text: EvSettingView.videoPath
        anchors.verticalCenter: fileDialogBtn.verticalCenter
        anchors.top: fileDialogBtn.bottom
        anchors.topMargin: 30
        font.pixelSize: 15
    }

    FileDialog {
        id: videoDialog
        title: qsTr("请选择视频文件")
        folder: shortcuts.home
        onAccepted: {
            EvSettingView.videoPath = String(fileUrl)
            console.log(EvSettingView.videoPath)
        }
        onRejected: {
        }
    }

    function setVideoBtn() {
        if(EvSettingView.cameraOn) {
            EvSettingView.cameraOn = false;
            fileDialogBtn.visible = true;
            videoPath.visible = true;
        } else {
            EvSettingView.cameraOn = true;
            fileDialogBtn.visible = false;
            videoPath.visible = false;
        }
    }

}
