import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import MMaterial

import Qcm.Material as MD

import "themes"

Rectangle {
    id: root
    color: "#2B2A22"

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

    property int tabWidth: 804
    property int tabHeight: 705
    property int tabTopLeftRadius: 100
    property string tabColor: MD.Token.color.surface

    property color controlMenuColor: MD.Token.color.inverse_on_surface
    property color lineColor: MD.Token.color.on_secondary_container
    property color fontColor: MD.Token.color.on_secondary_container

    property int smallControlMenuSpacing: 100

    property int fontSize: Size.pixel16

    property int margin: 52

    // Main tab Overview
    Rectangle {
        width: root.tabWidth
        height: root.tabHeight
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: root.tabColor
        topLeftRadius: root.tabTopLeftRadius

        visible: root.currentTabState === MainWindowView.TabState.Overview

        ColumnLayout {
            width: root.tabWidth - 104

            RowLayout {
                Layout.leftMargin: root.margin
                Layout.topMargin: root.margin
                spacing: root.smallControlMenuSpacing

                ProfilesView {
                    id: profilesMenu

                    model: mainWindow.configListModel

                    color: root.controlMenuColor
                    lineColor: root.lineColor

                    fontColor: root.fontColor
                    fontSize: root.fontSize

                    labelColor: root.fontColor
                    labelText: qsTr("Profiles")
                    labelLeftMargin: 23

                    Layout.alignment: Qt.AlignLeft
                }


                ControlMenu {
                    color: root.controlMenuColor

                    labelColor: root.fontColor
                    labelText: qsTr("Stats")
                    labelLeftMargin: 31

                    lineColor: root.lineColor

                    Layout.alignment: Qt.AlignRight
                }
            }

            ControlMenu {
                color: root.controlMenuColor

                labelColor: root.fontColor
                labelText: qsTr("Log")
                labelLeftMargin: 36

                lineColor: root.lineColor

                Layout.fillWidth: true
                Layout.leftMargin: root.margin
                Layout.topMargin: 23
                verticalLineLeftMargin: 99.5

                MSwitch {
                    id: autoScrollSwitch
                    accent: Theme.primary
                    text: qsTr("Auto Scroll")
                    label.color: root.fontColor
                    label.font.pixelSize: root.fontSize;
                    size: Size.Grade.M
                    anchors.top: parent.top
                    anchors.topMargin: 5.5
                    anchors.left: parent.verticalLine.right
                    anchors.leftMargin: 58.5 
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

                        onTextChanged: {
                            if (autoScrollSwitch.checked)
                                logView.ScrollBar.vertical.position = 1.0 - logView.ScrollBar.vertical.size
                        }
                    }
                }
            }
        }
    }

    // Additional tab Settings
    Rectangle {
        width: root.tabWidth
        height: root.tabHeight
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: root.tabColor
        topLeftRadius: root.tabTopLeftRadius
        visible: root.currentTabState === MainWindowView.TabState.Settings

        ColumnLayout {
            width: root.tabWidth - 104

            RowLayout {
                Layout.leftMargin: root.margin
                Layout.topMargin: root.margin
                spacing: root.smallControlMenuSpacing

                ControlMenu {
                    color: root.controlMenuColor

                    labelColor: root.fontColor
                    labelText: qsTr("Settings")
                    labelLeftMargin: 20

                    lineColor: root.lineColor

                    Layout.alignment: Qt.AlignLeft

                    ColumnLayout {
                        anchors.top: parent.horizontalLine.bottom
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.margins: 16

                        spacing: 15

                        RowLayout {
                            MCheckbox {
                                id: startOnBootCheck
                                accent: Theme.primary

                                implicitHeight: Size.pixel22
                                implicitWidth: Size.pixel22
                            }

                            Label { text: qsTr("Start on boot"); font.pixelSize: 16; Layout.leftMargin: 12; color: root.fontColor; font.weight: 600 }
                        }

                        RowLayout {
                            MCheckbox {
                                id: autoUpdatesCheck
                                accent: Theme.primary

                                implicitHeight: Size.pixel22
                                implicitWidth: Size.pixel22
                            }

                            Label { text: qsTr("Automatic updates"); font.pixelSize: 16; Layout.leftMargin: 12; color: root.fontColor; font.weight: 600 }
                        }

                        RowLayout {
                            MCheckbox {
                                id: preReleaseCheck
                                accent: Theme.primary

                                implicitHeight: Size.pixel22
                                implicitWidth: Size.pixel22
                            }

                            Label { text: qsTr("Pre-release"); font.pixelSize: 16; Layout.leftMargin: 12; color: root.fontColor; font.weight: 600 }
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
                    color: root.controlMenuColor

                    labelColor: root.fontColor
                    labelText: qsTr("Proxied apps")

                    lineColor: root.lineColor

                    labelLeftMargin: 10
                    verticalLineLeftMargin: 114.5

                    Layout.alignment: Qt.AlignRight
                }
            }

            ControlMenu {
                color: root.controlMenuColor

                labelColor: root.fontColor
                labelText: qsTr("Domain routing")
                labelLeftMargin: 10

                lineColor: root.lineColor

                Layout.fillWidth: true
                Layout.leftMargin: root.margin
                Layout.topMargin: 23
                verticalLineLeftMargin: 132.5

                MSwitch {
                    accent: Theme.primary
                    text: qsTr("Blacklist")
                    label.color: root.fontColor
                    label.font.pixelSize: root.fontSize;
                    size: Size.Grade.M
                    anchors.left: parent.verticalLine.right
                    anchors.top: parent.top
                    anchors.leftMargin: 42.5
                    anchors.topMargin: 5.5
                }
            }
        }
    }

    ColumnLayout {
        width: 196
        anchors.left: parent.left

        MenuButton {
            Layout.preferredWidth: 175
            Layout.topMargin: 30
            checked: root.currentTabState === MainWindowView.TabState.Overview
            icon.name: MD.Token.icon.account_circle_filled
            text: qsTr("Overview")

            onClicked: root.currentTabState = MainWindowView.TabState.Overview
        }

        MenuButton {
            Layout.preferredWidth: 175
            Layout.topMargin: 35
            checked: root.currentTabState === MainWindowView.TabState.Settings
            icon.name: MD.Token.icon.settings
            text: qsTr("Settings")

            onClicked: root.currentTabState = MainWindowView.TabState.Settings
        }

        MFabButton {
            accent: mainWindow.runnigState ?
                        Theme.primary :
                        Theme.secondary
            radius: 28
            Layout.preferredWidth: 96
            Layout.preferredHeight: 96
            Layout.topMargin: 209
            Layout.alignment: Qt.AlignHCenter

            leftIcon.iconData: mainWindow.runnigState ?
                                   Icons.light.pause :
                                   Icons.light.playArrow
            leftIcon.size: Size.pixel36

            onClicked: {
                mainWindow.runnigState ?
                    mainWindow.stopProxy() :
                    mainWindow.startProxy()
            }
        }
    }
}
