import QtQuick
import QtQuick.Layouts
import Qcm.Material as MD


RowLayout {
    id: root

    property string content

    property url linkUrl
    property string linkText

    property color linkColor: MD.Token.color.on_secondary_container
    property int linkWeight: 700
    property string linkDecoration: "none"
    property var typescale: MD.Token.typescale.title_medium

    property string iconName: MD.Token.icon.open_in_new
    property bool iconShow: true
    property bool iconOnLeft: false
    spacing: 2

    readonly property int _idx: content.indexOf("%1")
    readonly property string _before: _idx >= 0 ? content.slice(0, _idx) : content
    readonly property string _after:  _idx >= 0 ? content.slice(_idx + 2) : ""

    MD.Text {
        visible: root._before.length > 0
        textFormat: Text.RichText
        wrapMode: Text.Wrap
        typescale: root.typescale
        color: root.linkColor
        text: root._before
        Layout.alignment: Qt.AlignBaseline
    }

    MD.Icon {
        id: leftIcon
        visible: root.iconShow && root.iconOnLeft
        name: root.iconName
        size: linkText.font.pixelSize
        color: root.linkColor
        Layout.alignment: Qt.AlignBaseline
        Layout.topMargin: 7

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: if (root.linkUrl) Qt.openUrlExternally(root.linkUrl)
        }
    }

    RichLinkText {
        id: linkText
        Layout.alignment: Qt.AlignBaseline
        content: "%1"
        linkUrl: root.linkUrl
        linkText: root.linkText
        linkColor: root.linkColor
        linkWeight: root.linkWeight
        linkDecoration: root.linkDecoration
    }

    MD.Icon {
        id: rightIcon
        visible: root.iconShow && !root.iconOnLeft
        name: root.iconName
        size: linkText.font.pixelSize
        color: root.linkColor
        Layout.alignment: Qt.AlignVCenter
        Layout.topMargin: 3
        Layout.rightMargin: 2

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: if (root.linkUrl) Qt.openUrlExternally(root.linkUrl)
        }
    }

    MD.Text {
        visible: root._after.length > 0
        textFormat: Text.RichText
        wrapMode: Text.Wrap
        typescale: MD.Token.typescale.title_medium
        color: root.linkColor
        text: root._after
        Layout.alignment: Qt.AlignBaseline
    }
}
