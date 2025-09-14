import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "../controls"
import "../cards"

BasicTab {
    id: root

    property color fontColor: MD.Token.color.on_secondary_container

    contentItem: Item {
        GridLayout {
            id: gridLayout
            anchors.fill: parent
            columns: 2
            rows: 2
            rowSpacing: 20
            columnSpacing: 4

            SettingsCard {
                id: settingsCard

                Layout.row: 0
                Layout.column: 0
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
                Layout.preferredHeight: 320
            }

            UpdaterCard {
                id: updaterCard

                Layout.row: 0
                Layout.column: 1
                Layout.alignment: Qt.AlignRight
                Layout.fillWidth: true
                Layout.preferredHeight: 320
            }

            RoutingCard {
                id: routingCard
                visible: true

                Layout.row: 1
                Layout.column: 0
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
                Layout.preferredHeight: 350
            }

            ProxiedAppsCard {
                id: proxiedAppsCard
                visible: true

                Layout.row: 1
                Layout.column: 1
                Layout.alignment: Qt.AlignRight
                Layout.fillWidth: true
                Layout.preferredHeight: 350
            }
        }
    }
}
