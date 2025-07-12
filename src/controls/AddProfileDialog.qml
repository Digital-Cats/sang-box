import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qcm.Material as MD

MD.Dialog {
    id: root

    mdState.backgroundColor: MD.Token.color.secondary_container

    // TODO: Move it to C++
    enum ConfigType {
        Local,
        Remote
    }

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
            spacing: 15

            MD.TextField {
                Layout.fillWidth: true
                implicitHeight: 35
                type: MD.Enum.TextFieldOutlined
                placeholderText: qsTr("Name")
            }

            MD.ComboBox {
                id: profileTypeComboBox
                Layout.fillWidth: true
                textRole: "text"
                valueRole: "value"
                implicitHeight: 35
                model: [
                    { value: AddProfileDialog.ConfigType.Local, text: qsTr("Local") },
                    { value: AddProfileDialog.ConfigType.Remote, text: qsTr("Remote") }
                ]
            }

            RowLayout {
                Layout.fillWidth: true
                visible: profileTypeComboBox.currentValue === AddProfileDialog.ConfigType.Local

                MD.TextField {
                    Layout.fillWidth: true
                    implicitHeight: 35
                    type: MD.Enum.TextFieldOutlined
                    placeholderText: qsTr("Location")
                }

                MD.IconButton {
                    type: MD.Enum.BtOutlined
                    icon.name: MD.Token.icon.library_add
                    Layout.alignment: Qt.AlignVCenter
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 15
                visible: profileTypeComboBox.currentValue === AddProfileDialog.ConfigType.Remote

                MD.TextField {
                    Layout.fillWidth: true
                    implicitHeight: 35
                    type: MD.Enum.TextFieldOutlined
                    placeholderText: qsTr("URL")
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 15

                    MD.TextField {
                        Layout.fillWidth: true
                        implicitHeight: 35
                        type: MD.Enum.TextFieldOutlined
                        placeholderText: qsTr("Refresh (min)")
                        text: "60"
                        enabled: isRefreshEnable.checked
                    }

                    MDSwitch {
                        id: isRefreshEnable
                        text: qsTr("Enable")
                        Layout.alignment: Qt.AlignVCenter
                        checked: true
                        targetWidth: 39
                    }
                }
            }
        }
    }

    background: MD.ElevationRectangle {
        implicitWidth: 300
        implicitHeight: 300

        radius: MD.Token.shape.corner.medium
        color: mdState.backgroundColor
        elevation: mdState.elevation
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
            text: qsTr("Save")
            type: MD.Enum.BtText
            mdState.textColor: MD.Token.color.on_secondary_container
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
        }
    }
}
