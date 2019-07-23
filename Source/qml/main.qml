import QtQuick 2.13
import QtQuick.Window 2.13

Item {
    visible: true
    width: 640
    height: 480

    Image {
        id: evShowFrame
        cache: false
        anchors.centerIn: parent
        anchors.fill: parent
    }
    Connections {
        target: EvVideoCaptureView
        onFrameChanged: {
            evShowFrame.source="";
            evShowFrame.source="image://img";
        }
    }


}
