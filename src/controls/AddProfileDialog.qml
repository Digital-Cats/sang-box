import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qcm.Material as MD

MD.Dialog {
    id: root

    mdState.backgroundColor: MD.Token.color.secondary_container

    header: Item {
        height: 40

        LinedHeader {
            id: header

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left

            height: 30

            labelText: qsTr("Add Profile")
        }
    }

    contentItem: Item {
        ColumnLayout {
            anchors.fill: parent
            anchors.top: header.bottom
            spacing: 13

            MD.TextField {
                Layout.fillWidth: true
                type: MD.Enum.TextFieldFilled
                placeholderText: 'Name'
            }

            MD.ComboBox {
                Layout.fillWidth: true
                model: ["Local", "Remote"]
            }
        }
    }

    footer: MD.DialogButtonBox {
        topPadding: 120
        bottomPadding: 16

        MD.Button {
            text: qsTr("Cancel")
            type: MD.Enum.BtText
            mdState.textColor: MD.Token.color.on_secondary_container
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
        }

        MD.Button {
            text: qsTr("Save")
            type: MD.Enum.BtText
            mdState.textColor: MD.Token.color.on_secondary_container
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
        }
    }
}
