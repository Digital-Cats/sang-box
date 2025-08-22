import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qcm.Material as MD

MD.Dialog {
    id: root

    property string text

    title: qsTr("Error!")
    standardButtons: Dialog.Close
    mdState.backgroundColor: MD.Token.color.secondary_container
    horizontalPadding: 16

    header: MD.Control {
        topPadding: 16
        horizontalPadding: root.horizontalPadding
            contentItem: MD.Label {
            text: root.title
            color: MD.Token.color.on_secondary_container
            typescale: MD.Token.typescale.title_medium
        }
    }

    contentWidth: 300 - root.horizontalPadding * 2
    contentHeight: label.contentHeight
    contentItem: Item {
        MD.Label {
            id: label
            width: parent.width
            typescale: MD.Token.typescale.body_large
            color: MD.Token.color.on_secondary_container
            wrapMode: Label.Wrap
            // TODO: Remove after MR
            // https://github.com/hypengw/QmlMaterial/pull/10
            maximumLineCount: 999
            text: root.text
        }
    }
}
