import QtQuick 2.0

MouseArea {
    id: root
    property alias text: label.text
    property alias fontcolor: label.color
    property alias fontsize: label.font.pixelSize

    Rectangle {
        anchors.fill: parent
        anchors.centerIn: parent

    }
    Text{
        id: label
        text: "button"
        color: "blue"
        anchors.centerIn: parent
        font.pixelSize: 15
    }
}
