import QtQuick
import QtQuick.Layouts
import Qcm.Material as MD

MD.Text {
    id: root

    property string content: ""

    property url linkUrl: ""
    property string linkText: ""

    property color linkColor: MD.Token.color.on_secondary_container
    property int linkWeight: 700
    property string linkDecoration: "none"

    readonly property string linkCss:
        "<style>a, a:link, a:visited { " +
        "text-decoration:" + linkDecoration + "; " +
        "font-weight:" + linkWeight + "; " +
        "color:" + linkColor + "; }</style>"

    function anchorHtml() {
        var txt = linkText && linkText.length ? linkText : (linkUrl ? linkUrl : "");
        return "<a href='" + linkUrl + "'>" + txt + "</a>";
    }

    readonly property string _baseHtml: {
        if (linkUrl && content.indexOf("%1") !== -1)
            return content.arg(anchorHtml());
        if (linkUrl && (!content || content.length === 0))
            return anchorHtml();
        return content;
    }

    textFormat: Text.RichText
    typescale: MD.Token.typescale.title_medium
    color: linkColor
    text: linkCss + _baseHtml

    onLinkActivated: (url) => Qt.openUrlExternally(url)

    HoverHandler {
        enabled: root.hoveredLink.length > 0
        cursorShape: Qt.PointingHandCursor
    }
}
