import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import MMaterial

Rectangle {
    id: root
    radius: 12

    Layout.preferredWidth: 300
    Layout.preferredHeight: 300

    property color labelColor
    property color lineColor
    property int lineHeight: 30
    property int lineThickness: 1
    property int fontWeight: 600
    property int fontSize: 16

    property alias label: label
    property alias labelText: label.labelText
    property alias labelLeftMargin: label.anchors.leftMargin
    property alias labelTopMargin: label.anchors.topMargin
    property alias verticalLineLeftMargin: verticalLine.anchors.leftMargin
    property alias horizontalLine: horizontalLine
    property alias verticalLine: verticalLine

    Rectangle {
        id: horizontalLine
        color: root.lineColor
        height: root.lineThickness
        width: parent.width

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: root.lineHeight
    }

    Rectangle {
        id: verticalLine
        color: root.lineColor
        width: root.lineThickness
        height: root.lineHeight

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 99.5
    }

    Label {
        id: label
        color: root.labelColor
        property string labelText
        text: labelText
        font.pixelSize: root.fontSize;
        font.weight: root.fontWeight

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 5
    }
}
