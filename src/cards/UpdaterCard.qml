import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "../controls"

ControlCard {
    id: root

    labelText: qsTr("Updater")

    contentItem: Item {
        anchors.top: parent.header.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 16
        anchors.topMargin: 16

        ColumnLayout {
            spacing: 16
            anchors.fill: parent
            anchors.leftMargin: 16
            anchors.rightMargin: 16
            anchors.bottomMargin: 16

            RowLayout {
                Label {
                    id: appVersionLabel
                    text: qsTr("App version:")
                    font.pixelSize: 16
                    color: MD.Token.color.on_secondary_container
                }
                Label {
                    text: mainWindow.updater.appVersion
                    font.pixelSize: 16
                    color: "#00AC00"
                    Layout.leftMargin: 130 - root.contentItem.anchors.leftMargin - appVersionLabel.width
                }
            }

            RowLayout {
                Label {
                    id: coreLabel
                    text: qsTr("Core version:")
                    font.pixelSize: 16
                    color: MD.Token.color.on_secondary_container
                }
                VersionLabel {
                    id: coreVersionLabel
                    text: mainWindow.updater.coreVersion
                    newest: mainWindow.updater.isCoreNewest
                    font.pixelSize: 16
                    Layout.leftMargin: 130 - root.contentItem.anchors.leftMargin - coreLabel.width

                    Connections {
                        target: mainWindow.updater
                        function onIsCoreNewestChanged()
                        {
                            coreVersionLabel.newest = mainWindow.updater.isCoreNewest;
                        }
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }

            RowLayout {
                Layout.alignment: Qt.AlignBottom | Qt.AlignRight

                // Item {
                //     Layout.fillWidth: true
                // }

                MD.BusyButton {
                    id: updateButton
                    checkable: true
                    busy: false
                    icon.name: MD.Token.icon.download
                    text: 'Update'
                    Layout.rightMargin: 16

                    onClicked: {
                        updateButton.busy = true;
                        mainWindow.updater.requestLatestCoreVersion()
                    }

                    Connections {
                        target: mainWindow.updater
                        function onLatestCoreVersionChanged() {
                            updateButton.busy = false;
                        }
                    }
                }
            }
        }

    }
}
