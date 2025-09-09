import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "../controls"

ControlCard {
    labelText: qsTr("Log")

    headerHeight: 38
    header.contentItem: Item {
        RowLayout {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8

            MDSwitch {
                id: autoScrollSwitch
                Layout.alignment: Qt.AlignVCenter
                Layout.leftMargin: 16
                targetWidth: 52
            }

            MD.Label {
                Layout.alignment: Qt.AlignVCenter

                text: qsTr("Auto Scroll")
                color: MD.Token.color.on_secondary_container
                typescale: MD.Token.typescale.title_medium
            }
        }
    }

    contentItem: Item {
        QMD.ScrollView {
            id: logView

            anchors.fill: parent
            anchors.topMargin: 16
            anchors.leftMargin: 16

            contentWidth: parent.width - 16

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
