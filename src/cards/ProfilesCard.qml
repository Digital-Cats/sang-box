import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import modules.config

import "../controls"

ControlCard {
    id: root

    property var model

    labelText: qsTr("Profiles")

    contentItem: QMD.ScrollView {
        Layout.fillWidth: true
        Layout.fillHeight: true
        anchors.top: parent.header.bottom
        anchors.topMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 16
        spacing: 15

        ListView {
            id: profilesList

            anchors.fill: parent
            model: root.model

            delegate: RowLayout {
                id: profileDelegate

                width: parent.width

                MD.RadioButton {
                    checked: model.selected
                    onClicked: {
                        root.model.switchConfig(index)
                    }
                }

                MD.Label {
                    text: model.name
                    typescale: root.typescale
                    color: root.labelColor
                }

                Item {
                    Layout.fillWidth: true
                }

                MD.IconButton {
                    icon.name: MD.Token.icon.more_vert

                    onClicked: {
                        //Roker2: It's strange, but it works via this way
                        configMenu.configType = model.type
                        configMenu.popup()
                    }
                }

                ProfileContextMenu {
                    id: configMenu

                    onUpdateConfig: {
                        root.model.updateRemoteConfig(index)
                    }
                    onDeleteConfig: deleteDialog.open()
                }

                DeleteProfileDialog {
                    id: deleteDialog

                    anchors.centerIn: parent
                    parent: Overlay.overlay
                    profileName: model.name

                    onAccepted: {
                        root.model.deleteConfig(index)
                    }
                }
            }
        }

        AddProfileDialog {
            id: addProfileDialog

            anchors.centerIn: Overlay.overlay
            parent: Overlay.overlay

            onAccepted: {
                root.model.importConfigData(currentConfigType, generateDataForCurrentType())
                addProfileDialog.resetForm()
            }
            onRejected: addProfileDialog.resetForm()
        }

        AddNewProfileButton {
            y: profilesList.contentHeight
            width: parent.width

            onClicked: {
                addProfileDialog.open()
            }
        }
    }
}
