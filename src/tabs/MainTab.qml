import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts

import Qcm.Material as MD

import "../controls"
import "../cards"

BasicTab {
    id: root

    contentItem: Item {
        GridLayout {
            id: gridLayout
            anchors.fill: parent
            columns: 3
            rows: 2
            rowSpacing: 20
            columnSpacing: 4

            ProfilesCard {
                id: profilesCard

                Layout.row: 0
                Layout.column: 0
                Layout.preferredWidth: 280
                Layout.preferredHeight: 320

                model: mainWindow.configListModel
            }

            SelectorCard {
                id: selectorCard

                visible: false
                Layout.row: 0
                Layout.column: 1
                Layout.preferredWidth: 252
                Layout.preferredHeight: 320
            }

            StatsCard {
                id: statsCard

                visible: false
                Layout.row: 0
                Layout.column: 2
                Layout.preferredWidth: 200
                Layout.preferredHeight: 320
            }

            LogsCard {
                id: logsCard

                Layout.row: 1
                Layout.column: 0
                Layout.columnSpan: 3
                Layout.fillWidth: true
                Layout.preferredHeight: 350
            }
        }
    }
}
