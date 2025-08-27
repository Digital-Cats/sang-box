import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "../controls"

ControlCard {
    id: root

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
