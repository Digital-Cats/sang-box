import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "controls"

ControlMenu {
    id: root

    property var model
    property int fontSize: root.typescale.size

    labelText: qsTr("Profiles")

    QMD.ScrollView {
        Layout.fillWidth: true
        Layout.fillHeight: true
        anchors.top: parent.horizontalLine.bottom
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
                        MD.Util.showPopup(configMenu, {}, this)
                    }
                }

                Component {
                    id: configMenu
                    MD.Menu {
                        MD.Action {
                            text: qsTr("Update")
                            icon.name: MD.Token.icon.download
                        }

                        MD.Action {
                            text: qsTr("Edit")
                            icon.name: MD.Token.icon.edit
                            onTriggered: root.model.editConfig(index)
                        }

                        MD.Action {
                            text: qsTr("Delete")
                            icon.name: MD.Token.icon.delete
                            onTriggered: {
                                deleteDialog.open()
                            }
                        }
                    }
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

        AddNewProfileButton {
            y: profilesList.contentHeight
            width: parent.width

            onClicked: {
                model.importConfig()
            }
        }
    }
}
