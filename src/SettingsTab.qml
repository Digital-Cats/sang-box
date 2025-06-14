import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "controls"

BasicTab {
    id: root

    property int smallControlMenuSpacing: 100
    property color fontColor: MD.Token.color.on_secondary_container

    contentItem: Item {
        ColumnLayout {
            RowLayout {
                Layout.fillWidth: true
                spacing: root.smallControlMenuSpacing

                ControlMenu {
                    labelText: qsTr("Settings")

                    Layout.alignment: Qt.AlignLeft

                    ColumnLayout {
                        anchors.top: parent.horizontalLine.bottom
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.margins: 16

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
                            id: autoUpdatesCheck
                            visible: false

                            labelText: qsTr("Automatic updates")
                            checked: mainWindow.settings.isAutoUpdate

                            onClicked: {
                                mainWindow.settings.isAutoUpdate = !mainWindow.settings.isAutoUpdate
                            }
                        }

                        LabeledCheckbox {
                            id: preReleaseCheck
                            visible: false

                            labelText: qsTr("Pre-release")
                            checked: mainWindow.settings.isPreRelease

                            onClicked: {
                                mainWindow.settings.isPreRelease = !mainWindow.settings.isPreRelease
                            }
                        }

                        ColumnLayout {
                            Layout.topMargin: 10
                            spacing: 5

                            RowLayout {
                                Label { text: qsTr("App version:"); font.pixelSize: 16; Layout.leftMargin: 3; color: root.fontColor }
                                Label { text: mainWindow.settings.appVersion; font.pixelSize: 16; color: "#00AC00"; Layout.leftMargin: 5 }
                            }

                            RowLayout {
                                Label { text: qsTr("Core version:"); font.pixelSize: 16; Layout.leftMargin: 3; color: root.fontColor }
                                Label { text: mainWindow.settings.coreVersion; font.pixelSize: 16; color: "#FFB4AB"; Layout.leftMargin: 5 }
                            }
                        }
                    }
                }


                ControlMenu {
                    Layout.alignment: Qt.AlignRight

                    visible: false
                    labelText: qsTr("Proxied apps")
                }
            }

            ControlMenu {
                labelText: qsTr("Domain routing")
                visible: false

                Layout.fillWidth: true
                Layout.topMargin: 23

                RowLayout {
                    anchors.verticalCenter: parent.verticalLine.verticalCenter
                    anchors.left: parent.verticalLine.right
                    anchors.leftMargin: 42.5
                    spacing: 16

                    QMD.Switch {
                        Layout.alignment: Qt.AlignVCenter
                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 39
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
    }
}
