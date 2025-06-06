import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import Qcm.Material as MD

import "controls"

Rectangle {
    id: root
    color: MD.Token.color.neutral_10

    enum TabState {
        Overview,
        Settings
    }
    
    enum WorkState {
        Start,
        Stop
    }

    property int currentTabState: MainWindowView.TabState.Overview
    property int currentWorkState: MainWindowView.WorkState.Stop

    // Main tab Overview
    MainTab {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: root.currentTabState === MainWindowView.TabState.Overview
    }

    // Additional tab Settings
    SettingsTab {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: root.currentTabState === MainWindowView.TabState.Settings
    }

    ColumnLayout {
        width: 196
        anchors.left: parent.left

        MenuButton {
            Layout.preferredWidth: big_width
            Layout.topMargin: 30
            big_width: 175
            checked: root.currentTabState === MainWindowView.TabState.Overview
            icon.name: MD.Token.icon.account_circle_filled
            text: qsTr("Overview")

            onClicked: root.currentTabState = MainWindowView.TabState.Overview
        }

        MenuButton {
            Layout.preferredWidth: big_width
            Layout.topMargin: 35
            big_width: 175
            checked: root.currentTabState === MainWindowView.TabState.Settings
            icon.name: MD.Token.icon.settings
            text: qsTr("Settings")

            onClicked: root.currentTabState = MainWindowView.TabState.Settings
        }

        PlayButton {
            Layout.preferredWidth: 96
            Layout.preferredHeight: 96
            Layout.topMargin: 209
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
