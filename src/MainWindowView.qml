import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import Qcm.Material as MD

import "controls"

Rectangle {
    id: root
    color: MD.Token.color.surface_container

    enum TabState {
        Overview,
        Settings
    }

    property int currentTabState: MainWindowView.TabState.Overview

    // Main tab Overview
    MainTab {
        anchors.top: parent.top
        anchors.left: verticalMenu.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 45
        visible: root.currentTabState === MainWindowView.TabState.Overview
    }

    // Additional tab Settings
    SettingsTab {
        anchors.top: parent.top
        anchors.left: verticalMenu.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 45
        visible: root.currentTabState === MainWindowView.TabState.Settings
    }

    ColumnLayout {
        id: verticalMenu

        width: 196
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Item {
            Layout.preferredHeight: 120
            Layout.preferredWidth: 120
            Layout.topMargin: 25
            Layout.leftMargin: 38

            Image {
                id: sang_logo
                anchors.leftMargin: 2
                anchors.topMargin: 24
                source: "qrc:/images/sang_logo.svg"
                height: 55
                width: 115
                sourceSize.height: 55
                sourceSize.width: 115
            }

            FontLoader {
                id: lexendDeca
                source: "qrc:/fonts/LexendDeca-Regular.ttf"
            }

            MD.Label {
                anchors.top: sang_logo.bottom
                anchors.leftMargin: 1
                anchors.topMargin: 6
                typescale: MD.Token.typescale.title_large
                text: "sang-box"
                color: MD.Token.color.on_surface
                font: lexendDeca.font
            }
        }

        MenuButton {
            Layout.preferredHeight: 52
            Layout.preferredWidth: 170
            Layout.topMargin: 39
            checked: root.currentTabState === MainWindowView.TabState.Overview
            icon.name: MD.Token.icon.account_circle
            text: qsTr("Overview")

            onClicked: root.currentTabState = MainWindowView.TabState.Overview
        }

        MenuButton {
            Layout.preferredHeight: 52
            Layout.preferredWidth: 170
            Layout.topMargin: 35
            checked: root.currentTabState === MainWindowView.TabState.Settings
            icon.name: MD.Token.icon.settings
            text: qsTr("Settings")

            onClicked: root.currentTabState = MainWindowView.TabState.Settings
        }

        Item {
            Layout.fillHeight: true
        }

        PlayButton {
            Layout.preferredWidth: 96
            Layout.preferredHeight: 96
            Layout.bottomMargin: 127
            Layout.alignment: Qt.AlignHCenter
            checked: mainWindow.runnigState

            onClicked: {
                mainWindow.runnigState ?
                    mainWindow.stopProxy() :
                    mainWindow.startProxy()
            }
        }
    }
}
