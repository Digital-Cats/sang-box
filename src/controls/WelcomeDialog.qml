import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import QtCore

import Qcm.Material as MD

import modules.config

MD.Dialog {
    id: root
    property color fontColor: MD.Token.color.on_secondary_container

    mdState.backgroundColor: MD.Token.color.secondary_container
    horizontalPadding: 17

    header: Item {
        height: 30

        LinedHeader {
            id: header

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left

            height: 30

            labelText: qsTr("Welcome!")
        }
    }

    contentItem: Item {
        ColumnLayout {
            anchors.fill: parent
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            spacing: 15

            Text {
                Layout.preferredWidth: 300
                text: qsTr("This app is nothing but an unofficial GUI for the proxy platform called sing-box")
                font.pixelSize: 16
                // Layout.leftMargin: 3
                color: root.fontColor
                wrapMode: Text.WordWrap
            }

            Text {
                Layout.preferredWidth: 300
                text: qsTr("The button below will download the core (i.e. sing-box) for you ^_________^")
                font.pixelSize: 16
                // Layout.leftMargin: 3
                color: root.fontColor
                wrapMode: Text.WordWrap
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

    background: MD.ElevationRectangle {
        implicitWidth: 300
        implicitHeight: 300

        radius: MD.Token.shape.corner.medium
        color: root.mdState.backgroundColor
        elevation: mdState.elevation
    }

    footer: MD.DialogButtonBox {
        bottomPadding: 16

        DialogButton {
            type: MD.Enum.BtElevated
            color: MD.Token.color.on_primary
            icon.name: MD.Token.icon.download
            text: qsTr("Download")
        }
    }
}
