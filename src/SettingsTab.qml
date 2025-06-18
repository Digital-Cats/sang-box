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
                id: proxiedAppsMenu
                visible: false

                Layout.alignment: Qt.AlignRight
                Layout.row: 0
                Layout.column: 1

                labelText: qsTr("Proxied apps")
            }

            ControlMenu {
                id: routingMenu
                visible: false

                Layout.row: 1
                Layout.column: 0
                Layout.columnSpan: 2
                Layout.fillWidth: true

                labelText: qsTr("Domain routing")

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
