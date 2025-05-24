import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import Qcm.Material as MD

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
    property int fontSize: root.typescale.size
    property MD.t_typescale typescale: MD.Token.typescale.title_medium

    property alias labelText: label.text
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

    MD.Label {
        id: label

        anchors.verticalCenter: root.verticalLine.verticalCenter
        anchors.left: parent.left

        color: root.labelColor
        typescale: root.typescale
    }
}
