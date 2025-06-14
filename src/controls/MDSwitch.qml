import QtQuick
import QtQuick.Controls.Material as QMD
import Qcm.Material as MD

MD.Switch {
    id: root
    property int targetWidth: root.implicitWidth
    readonly property real scaleFactor: root.implicitWidth > 0 ? root.targetWidth / root.implicitWidth : 1.0

    transform: Scale {
        origin.x: root.width / 2
        origin.y: root.height / 2
        xScale: root.scaleFactor
        yScale: root.scaleFactor
    }
}
