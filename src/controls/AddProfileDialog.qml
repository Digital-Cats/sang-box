import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import QtCore

import Qcm.Material as MD

import modules.config

MD.Dialog {
    id: root

    property alias currentConfigType: profileTypeComboBox.currentValue
    property alias profileName: profileNameField.text

    property alias filePath: locationField.text

    property alias urlPath: urlTextField.text

    function generateDataForCurrentType()
    {
        if (currentConfigType === Config.Local)
            return { "profileName": root.profileName, "filePath": root.filePath }
        else if (currentConfigType === Config.Remote)
            return { "profileName": root.profileName, "urlPath": root.urlPath }
        else
            return {}
    }

    mdState.backgroundColor: MD.Token.color.secondary_container
    horizontalPadding: 16

    header: Item {
        height: 30

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
            spacing: 8

            MD.TextField {
                id: profileNameField
                Layout.fillWidth: true
                implicitHeight: 48
                type: MD.Enum.TextFieldOutlined
                placeholderText: qsTr("Name")
            }

            MD.ComboBox {
                id: profileTypeComboBox
                Layout.fillWidth: true
                textRole: "text"
                valueRole: "value"
                implicitHeight: 48
                model: [
                    { value: Config.Local, text: qsTr("Local") },
                    { value: Config.Remote, text: qsTr("Remote") }
                ]
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 8
                visible: root.currentConfigType === Config.Local

                RowLayout {
                    MD.TextField {
                        id: locationField

                        Layout.fillWidth: true
                        implicitHeight: 48
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

                    Item {
                        Layout.fillWidth: true
                    }
                }

                Item {
                    Layout.fillHeight: true
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 8
                visible: root.currentConfigType === Config.Remote

                MD.TextField {
                    id: urlTextField

                    Layout.fillWidth: true
                    implicitHeight: 48
                    type: MD.Enum.TextFieldOutlined
                    placeholderText: qsTr("URL")
                }

                MD.TextField {
                    id: updateTimeField

                    implicitHeight: 40
                    type: MD.Enum.TextFieldOutlined
                    placeholderText: qsTr("Update (min) ")
                    text: "60"
                    // typescale: MD.Token.typescale.body_small

                    ToolTip.visible: hovered
                    ToolTip.delay: Application.styleHints.mousePressAndHoldInterval
                    ToolTip.text: qsTr("Value '0' disables auto-refresh")

                    onTextChanged: {
                        if (text.length === 0) {
                            text = "0";
                        }
                    }

                    validator: IntValidator {
                        bottom: 0
                        top: 9999
                    }
                }
            }
        }
    }

    background: MD.ElevationRectangle {
        implicitWidth: 300
        implicitHeight: 324

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

    function resetForm() {
        profileNameField.text = "";
        urlTextField.text = "";
        locationField.text = "";
        updateTimeField.text = "60";
        profileTypeComboBox.currentIndex = 0;
    }

    onAboutToHide: root.resetForm()

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
