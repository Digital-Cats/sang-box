import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import MMaterial

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

                            labelText: qsTr("Automatic updates")
                        }

                        LabeledCheckbox {
                            id: preReleaseCheck

                            labelText: qsTr("Pre-release")
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

                        MFabButton {
                            accent: Theme.primary
                            radius: 100
                            Layout.preferredWidth: 112
                            Layout.preferredHeight: 40
                            Layout.topMargin: 4
                            Layout.alignment: Qt.AlignRight

                            leftIcon.iconData: Icons.light.download
                            leftIcon.size: Size.pixel20

                            text: qsTr("Update")
                        }
                    }
                }


                ControlMenu {
                    Layout.alignment: Qt.AlignRight

                    labelText: qsTr("Proxied apps")
                }
            }

            ControlMenu {
                labelText: qsTr("Domain routing")

                Layout.fillWidth: true
                Layout.topMargin: 23

                MSwitch {
                    accent: Theme.primary
                    text: qsTr("Blacklist")
                    label.color: root.fontColor
                    label.font.pixelSize: parent.typescale.size;
                    size: Size.Grade.M
                    anchors.left: parent.verticalLine.right
                    anchors.top: parent.top
                    anchors.leftMargin: 42.5
                    anchors.topMargin: 5.5
                }
            }
        }
    }
}
