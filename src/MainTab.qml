import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "controls"

BasicTab {
    id: root

    contentItem: Item {
        GridLayout {
            id: gridLayout
            anchors.fill: parent
            columns: 2
            rows: 2
            rowSpacing: 23
            columnSpacing: 23

            ProfilesView {
                id: profilesMenu

                Layout.row: 0
                Layout.column: 0

                model: mainWindow.configListModel
            }

            ControlMenu {
                id: statsMenu
                visible: false

                Layout.alignment: Qt.AlignRight
                Layout.row: 0
                Layout.column: 1

                labelText: qsTr("Stats")
            }

            ControlMenu {
                id: logMenu

                Layout.row: 1
                Layout.column: 0
                Layout.columnSpan: 2
                Layout.fillWidth: true

                labelText: qsTr("Log")

                RowLayout {
                    anchors.verticalCenter: parent.verticalLine.verticalCenter
                    anchors.left: parent.verticalLine.right
                    anchors.leftMargin: 47.5
                    spacing: 7

                    MDSwitch {
                        id: autoScrollSwitch
                        Layout.alignment: Qt.AlignVCenter
                        targetWidth: 39
                    }

                    MD.Label {
                        Layout.alignment: Qt.AlignVCenter
                        text: qsTr("Auto Scroll")
                        color: MD.Token.color.on_secondary_container
                        typescale: MD.Token.typescale.title_medium
                    }
                }

                ScrollView {
                    id: logView
                    anchors.top: parent.horizontalLine.bottom
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 15

                    width: parent.width - 15
                    contentWidth: width

                    Text {
                        text: mainWindow.proxyOutput
                        width: parent.width
                        wrapMode: Text.WordWrap
                        color: MD.Token.color.on_secondary_container

                        onTextChanged: {
                            if (autoScrollSwitch.checked)
                                logView.ScrollBar.vertical.position = 1.0 - logView.ScrollBar.vertical.size
                        }
                    }
                }
            }
        }
    }
}
