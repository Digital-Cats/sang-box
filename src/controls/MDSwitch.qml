import QtQuick
import QtQuick.Controls.Material as QMD
import Qcm.Material as MD

MD.Switch {
    id: root
    property int targetWidth: root.implicitWidth
    readonly property real scaleFactor: root.targetWidth / 52.0

    implicitWidth: targetWidth
    implicitHeight: Math.round(32 * scaleFactor)

    transform: Scale {
        origin.x: root.width / 2
        origin.y: root.height / 2
        xScale: root.scaleFactor
        yScale: root.scaleFactor
    }
}
