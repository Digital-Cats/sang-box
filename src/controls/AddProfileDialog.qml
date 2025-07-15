import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import QtCore

import Qcm.Material as MD

MD.Dialog {
    id: root

    property alias currentConfigType: profileTypeComboBox.currentValue
    property alias filePath: locationField.text
    property alias profileName: profileNameField.text

    mdState.backgroundColor: MD.Token.color.secondary_container
    horizontalPadding: 17

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
                id: profileNameField
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

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 15
                visible: root.currentConfigType === AddProfileDialog.ConfigType.Local

                RowLayout {
                    MD.TextField {
                        id: locationField

                        Layout.fillWidth: true
                        implicitHeight: 35
                        type: MD.Enum.TextFieldOutlined
                        placeholderText: qsTr("Location")
                    }

                    MD.IconButton {
                        type: MD.Enum.BtOutlined
                        icon.name: MD.Token.icon.library_add
                        Layout.alignment: Qt.AlignVCenter
                        onClicked: {
                            fileDialog.open()
                        }
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 15
                visible: root.currentConfigType === AddProfileDialog.ConfigType.Remote

                MD.TextField {
                    Layout.fillWidth: true
                    implicitHeight: 35
                    type: MD.Enum.TextFieldOutlined
                    placeholderText: qsTr("URL")
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 0

                    MD.TextField {
                        implicitHeight: 35
                        implicitWidth: 129
                        type: MD.Enum.TextFieldOutlined
                        placeholderText: qsTr("Update (min)")
                        text: "60"
                        enabled: isRefreshEnable.checked
                        // typescale: MD.Token.typescale.body_small

                        onTextChanged: {
                            if (text.length === 0) {
                                text = "0";
                            }
                        }

                        validator: IntValidator {
                            bottom: 0
                            top: 100
                        }
                    }

                    MDSwitch {
                        id: isRefreshEnable
                        Layout.alignment: Qt.AlignVCenter
                        Layout.leftMargin: 11
                        checked: true
                        targetWidth: 39
                    }

                    MD.Label {
                        Layout.alignment: Qt.AlignVCenter
                        Layout.leftMargin: 14
                        text: qsTr("Enable")
                        typescale: MD.Token.typescale.title_medium
                        color: MD.Token.color.on_secondary_container
                    }

                    Item {
                        Layout.preferredWidth: 24
                        Layout.fillWidth: false
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

        DialogButton {
            text: qsTr("Cancel")
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
        }

        DialogButton {
            text: qsTr("Save")
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
        }
    }

    FileDialog {
        id: fileDialog

        fileMode: FileDialog.OpenFile
        options: FileDialog.ReadOnly
        nameFilters: qsTr("JSON File (*.json)")
        currentFolder: StandardPaths.standardLocations(StandardPaths.DownloadLocation)[0]

        onAccepted: {
            // https://stackoverflow.com/a/26868237
            var path = selectedFile.toString();
            // remove prefixed "file:///"
            path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            // unescape html codes like '%23' for '#'
            root.filePath = decodeURIComponent(path);
        }
    }
}
