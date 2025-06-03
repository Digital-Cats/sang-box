import QtQuick
import QtQuick.Controls

import Qcm.Material as MD

Control {
    id: root

    property color backgroundColor: MD.Token.color.surface
    property int topLeftRadius: 100

    width: 804
    height: 705
    leftPadding: 52
    rightPadding: 52
    topPadding: 52
    bottomPadding: 30

    background: Rectangle {
        anchors.fill: parent
        topLeftRadius: root.topLeftRadius
        color: root.backgroundColor
    }
}
