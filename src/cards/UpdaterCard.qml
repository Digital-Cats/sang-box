import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "../controls"

ControlCard {
    id: root

    labelText: qsTr("Updater")

    contentItem: Item {
        anchors.top: parent.header.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 16
        anchors.topMargin: 16

        ColumnLayout {
            spacing: 16
            anchors.fill: parent
            anchors.leftMargin: 16
            anchors.rightMargin: 16
            anchors.bottomMargin: 16

            RowLayout {
                Label {
                    id: appVersionLabel
                    text: qsTr("App version:")
                    font.pixelSize: 16
                    color: MD.Token.color.on_secondary_container
                }
                Label {
                    text: mainWindow.updater.appVersion
                    font.pixelSize: 16
                    color: "#00AC00"
                    Layout.leftMargin: 130 - root.contentItem.anchors.leftMargin - appVersionLabel.width
                }
            }

            RowLayout {
                Label {
                    id: coreLabel
                    text: qsTr("Core version:")
                    font.pixelSize: 16
                    color: MD.Token.color.on_secondary_container
                }
                VersionLabel {
                    id: coreVersionLabel
                    text: mainWindow.updater.coreVersion
                    newest: mainWindow.updater.isCoreNewest
                    font.pixelSize: 16
                    Layout.leftMargin: 130 - root.contentItem.anchors.leftMargin - coreLabel.width

                    Connections {
                        target: mainWindow.updater
                        function onIsCoreNewestChanged()
                        {
                            coreVersionLabel.newest = mainWindow.updater.isCoreNewest;
                        }
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }

            RowLayout {
                Layout.alignment: Qt.AlignBottom | Qt.AlignRight

                MD.BusyButton {
                    id: fetchBtn
                    checkable: true
                    busy: false
                    icon.name: MD.Token.icon.refresh
                    text: qsTr("Fetch")
                    visible: !mainWindow.updater.updateAvailable
                    Layout.rightMargin: 16

                    ToolTip.visible: hovered
                    ToolTip.delay: Application.styleHints.mousePressAndHoldInterval
                    ToolTip.text: qsTr("Check updates for core and app")

                    onClicked: {
                        fetchBtn.busy = true
                        mainWindow.updater.requestLatestCoreVersion()
                    }
                }

                MD.BusyButton {
                    id: updateBtn
                    checkable: true
                    busy: false
                    icon.name: MD.Token.icon.download
                    text: qsTr("Update")
                    enabled: !mainWindow.runnigState
                    visible: mainWindow.updater.updateAvailable
                    Layout.rightMargin: 16

                    ToolTip.visible: hovered && !enabled
                    ToolTip.text: qsTr("Disable proxy to update")

                    onClicked: {
                        updateBtn.busy = true
                        mainWindow.updater.updateCore()
                    }
                }

                Connections {
                    target: mainWindow.updater
                    function onLatestCoreVersionChanged() {
                        fetchBtn.busy = false
                    }
                    function onUpdateAvailableChanged()
                    {
                        fetchBtn.busy = false
                        updateBtn.busy = false
                    }
                }
            }
        }

    }
}
