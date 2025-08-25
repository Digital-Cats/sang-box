import QtQuick
import QtQuick.Controls

import Qcm.Material as MD

Control {
    id: root

    property color backgroundColor: MD.Token.color.surface_container
    property int topLeftRadius: 0

    leftPadding: 32
    rightPadding: 32
    topPadding: 30
    bottomPadding: 30

    background: Rectangle {
        anchors.fill: parent
        topLeftRadius: root.topLeftRadius
        color: "transparent"
    }
}
