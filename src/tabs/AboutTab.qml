// src/AboutTab.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qcm.Material as MD

import "../controls"

BasicTab {
    id: root

    contentItem: Item {
        ControlCard {
            id: aboutMenu
            anchors.fill: parent
            labelText: qsTr("About sang-box")

        }
    }
}
