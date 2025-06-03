import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import Qcm.Material as MD

Rectangle {
    id: root
    radius: 12
    color: MD.Token.color.inverse_on_surface

    Layout.preferredWidth: 300
    Layout.preferredHeight: 300

    property color lineColor: MD.Token.color.on_secondary_container
    property int lineHeight: 30
    property int lineThickness: 1
    property MD.t_typescale typescale: MD.Token.typescale.title_medium

    property alias labelColor: label.color
    property alias labelText: label.text
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
        anchors.leftMargin: Math.max(99.5, label.width + 10 * 2)
    }

    MD.Label {
        id: label

        anchors.verticalCenter: root.verticalLine.verticalCenter
        x: Math.max((99.5 - width) / 2, 10)
        color: MD.Token.color.on_secondary_container
        typescale: root.typescale
    }
}
