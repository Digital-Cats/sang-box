import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qcm.Material as MD

MD.Dialog {
    id: root

    property string profileName

    topPadding: 25
    bottomPadding: 16
    horizontalPadding: 16
    mdState.backgroundColor: MD.Token.color.secondary_container

    header: Item{}
    contentItem: Item {
        ColumnLayout {
            anchors.fill: parent
            MD.Label {
                Layout.fillWidth: true
                typescale: MD.Token.typescale.title_medium
                color: MD.Token.color.on_secondary_container
                text: qsTr("Delete %1?").arg(root.profileName)
            }

            MD.Label {
                Layout.fillWidth: true
                typescale: MD.Token.typescale.title_medium
                color: MD.Token.color.on_secondary_container
                text: qsTr("This action cannot be undone!")
            }
        }
    }

    footer: MD.DialogButtonBox {
        bottomPadding: 16

        MD.Button {
            text: qsTr("Cancel")
            type: MD.Enum.BtText
            mdState.textColor: MD.Token.color.on_secondary_container
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
        }

        MD.Button {
            text: qsTr("Delete")
            type: MD.Enum.BtText
            mdState.textColor: MD.Token.color.on_secondary_container
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
        }
    }
}
