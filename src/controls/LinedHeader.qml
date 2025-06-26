import QtQuick
import QtQuick.Controls

import Qcm.Material as MD

Control {
    id: root

    leftPadding: verticalLine.x + lineThickness
    bottomPadding: lineThickness

    property color lineColor: MD.Token.color.on_secondary_container
    property int lineThickness: 1
    property MD.t_typescale typescale: MD.Token.typescale.title_medium

    property alias labelColor: label.color
    property alias labelText: label.text

    Rectangle {
        id: horizontalLine

        color: root.lineColor
        height: root.lineThickness
        width: parent.width

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        id: verticalLine

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        x: Math.max(99.5, label.width + 10 * 2)

        color: root.lineColor
        width: root.lineThickness
    }

    MD.Label {
        id: label

        anchors.verticalCenter: verticalLine.verticalCenter
        x: Math.max((99.5 - width) / 2, 10)

        color: MD.Token.color.on_secondary_container
        typescale: root.typescale
    }
}
