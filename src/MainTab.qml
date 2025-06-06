import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "controls"

BasicTab {
    id: root

    property int smallControlMenuSpacing: 100

    contentItem: Item {
        ColumnLayout {
            RowLayout {
                spacing: root.smallControlMenuSpacing

                ProfilesView {
                    Layout.alignment: Qt.AlignLeft

                    model: mainWindow.configListModel
                    labelText: qsTr("Profiles")
                }


                ControlMenu {
                    Layout.alignment: Qt.AlignRight

                    labelText: qsTr("Stats")
                }
            }

            ControlMenu {
                Layout.fillWidth: true
                Layout.topMargin: 23

                labelText: qsTr("Log")

                RowLayout {
                    anchors.verticalCenter: parent.verticalLine.verticalCenter
                    anchors.left: parent.verticalLine.right
                    anchors.leftMargin: 58.5
                    spacing: 16

                    QMD.Switch {
                        id: autoScrollSwitch

                        Layout.alignment: Qt.AlignVCenter
                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 39
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
