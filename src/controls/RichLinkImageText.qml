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

    property url imageUrl: ""
    property bool imageShow: true
    property bool imageOnLeft: false
    property int imageWidth: 16
    property int imageHeight: 16
    property int imageGap: 2
    property int imageBaseline: Math.round(imageHeight * 0.72)

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

    Item {
        visible: root.imageShow && root.imageOnLeft
        Layout.alignment: Qt.AlignBaseline
        Layout.rightMargin: root.imageGap
        baselineOffset: root.imageBaseline
        width: root.imageWidth
        height: root.imageHeight

        Image {
            anchors.fill: parent
            source: root.imageUrl
            fillMode: Image.PreserveAspectFit
            asynchronous: true
            smooth: true
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: if (root.linkUrl) Qt.openUrlExternally(root.linkUrl)
        }
    }

    RichLinkText {
        id: link
        Layout.alignment: Qt.AlignBaseline
        Layout.rightMargin: 0
        content: "%1"
        linkUrl: root.linkUrl
        linkText: root.linkText
        linkColor: root.linkColor
        linkWeight: root.linkWeight
        linkDecoration: root.linkDecoration
    }

    Item {
        visible: root.imageShow && !root.imageOnLeft
        Layout.alignment: Qt.AlignBaseline
        Layout.leftMargin: root.imageGap
        baselineOffset: root.imageBaseline
        width: root.imageWidth
        height: root.imageHeight

        Image {
            anchors.fill: parent
            source: root.imageUrl
            fillMode: Image.PreserveAspectFit
            asynchronous: true
            smooth: true
        }
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
        typescale: root.typescale
        color: root.linkColor
        text: root._after
        Layout.alignment: Qt.AlignBaseline
    }
}
