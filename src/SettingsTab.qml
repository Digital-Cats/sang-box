import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "controls"

BasicTab {
    id: root

    property color fontColor: MD.Token.color.on_secondary_container

    contentItem: Item {
        GridLayout {
            id: gridLayout
            anchors.fill: parent
            columns: 2
            rows: 2
            rowSpacing: 23
            columnSpacing: 23

            ControlMenu {
                id: settingsMenu

                Layout.row: 0
                Layout.column: 0

                labelText: qsTr("Settings")

                contentItem: Item {
                    anchors.top: parent.header.bottom
                    anchors.left: parent.left
                    anchors.margins: 16
                    ColumnLayout {
                        spacing: 15

                        LabeledCheckbox {
                            id: startOnBootCheck

                            labelText: qsTr("Start on boot")
                            checked: mainWindow.settings.isAutoRun

                            onClicked: {
                                mainWindow.settings.isAutoRun = !mainWindow.settings.isAutoRun
                            }
                        }

                        LabeledCheckbox {
                            id: preReleaseCheck
                            visible: false

                            labelText: qsTr("Check for core updates")
                        }

                        LabeledCheckbox {
                            id: autoUpdatesCheck
                            visible: false

                            labelText: qsTr("Check for app updates")
                        }
                    }
                }
            }

            ControlMenu {
                id: updater

                Layout.row: 0
                Layout.column: 1

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
                                color: root.fontColor
                            }
                            Label {
                                text: mainWindow.updater.appVersion
                                font.pixelSize: 16
                                color: "#00AC00"
                                Layout.leftMargin: 130 - updater.contentItem.anchors.leftMargin - appVersionLabel.width
                            }
                        }

                        RowLayout {
                            Label {
                                id: coreLabel
                                text: qsTr("Core version:")
                                font.pixelSize: 16
                                color: root.fontColor
                            }
                            VersionLabel {
                                id: coreVersionLabel
                                text: mainWindow.updater.coreVersion
                                newest: mainWindow.updater.isCoreNewest
                                font.pixelSize: 16
                                Layout.leftMargin: 130 - updater.contentItem.anchors.leftMargin - coreLabel.width

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

            ControlMenu {
                id: routingMenu
                visible: false

                Layout.row: 1
                Layout.column: 0

                labelText: qsTr("Domain routing")

                header.contentItem: Item {
                    RowLayout {
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 16

                        MDSwitch {
                            id: blackListSwitch
                            Layout.alignment: Qt.AlignVCenter
                            Layout.leftMargin: 42
                            targetWidth: 39
                        }

                        MD.Label {
                            Layout.alignment: Qt.AlignVCenter
                            text: qsTr("Blacklist")
                            color: MD.Token.color.on_secondary_container
                            typescale: MD.Token.typescale.title_medium
                        }
                    }
                }
            }

            ControlMenu {
                id: proxiedAppsMenu
                visible: false

                Layout.alignment: Qt.AlignRight
                Layout.row: 1
                Layout.column: 1

                labelText: qsTr("Proxied apps")
            }
        }
    }
}
