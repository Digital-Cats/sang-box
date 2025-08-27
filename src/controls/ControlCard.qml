import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qcm.Material as MD

Control {
    id: root

    Layout.preferredWidth: 300
    Layout.preferredHeight: 300

    topPadding: headerHeight

    property int headerHeight: 30

    property alias typescale: header.typescale
    property alias labelColor: header.labelColor
    property alias labelText: header.labelText
    property alias header: header

    LinedHeader {
        id: header

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left

        height: root.headerHeight
    }

    background: Rectangle {
        anchors.fill: parent
        radius: 12
        color: MD.Token.color.secondary_container
    }
}
