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

    property url avatarUrl: ""
    property bool avatarShow: true
    property bool avatarOnLeft: false
    property int avatarSize: 16
    property bool avatarCircle: true
    property int avatarCorner: 6
    property int avatarGap: 4
    property int avatarBaseline: Math.round(avatarSize * 0.72)

    spacing: 0

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

    Canvas {
        id: leftAvatar
        visible: root.avatarShow && root.avatarOnLeft
        Layout.alignment: Qt.AlignBaseline
        Layout.rightMargin: root.avatarGap
        baselineOffset: avatarBaseline

        width: root.avatarSize
        height: root.avatarSize

        property url src: root.avatarUrl

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            ctx.save();

            var r = Math.min(width, height) / 2;
            ctx.beginPath();
            ctx.arc(width/2, height/2, r, 0, Math.PI*2, false);
            ctx.closePath();
            ctx.clip();

            ctx.drawImage(src, 0, 0, width, height);
            ctx.restore();
        }

        Component.onCompleted: {
            loadImage(src);
            requestPaint();
        }
        onImageLoaded: requestPaint();

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
        content: "%1"
        linkUrl: root.linkUrl
        linkText: root.linkText
        linkColor: root.linkColor
        linkWeight: root.linkWeight
        linkDecoration: root.linkDecoration
    }

    Canvas {
        id: rightAvatar
        visible: root.avatarShow && !root.avatarOnLeft
        Layout.alignment: Qt.AlignBaseline
        Layout.leftMargin: root.avatarGap
        baselineOffset: avatarBaseline

        width: root.avatarSize
        height: root.avatarSize

        property url src: root.avatarUrl

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            ctx.save();

            var r = Math.min(width, height) / 2;
            ctx.beginPath();
            ctx.arc(width/2, height/2, r, 0, Math.PI*2, false);
            ctx.closePath();
            ctx.clip();

            ctx.drawImage(src, 0, 0, width, height);
            ctx.restore();
        }

        Component.onCompleted: {
            loadImage(src);
            requestPaint();
        }
        onImageLoaded: requestPaint();

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
