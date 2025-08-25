import QtQuick
import QtQuick.Controls

Label {
    id: root
    property bool newest
    property color okColor: "#00AC00"
    property color badColor: "#FFB4AB"

    color: newest ? okColor : badColor
}
