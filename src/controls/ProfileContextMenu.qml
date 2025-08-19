import QtQuick

import Qcm.Material as MD

import modules.config

MD.Menu {
    id: root

    signal updateConfig()
    signal editConfig()
    signal deleteConfig()
    property var configType

    onAboutToShow: {
        while (root.count > 0) {
            root.removeItem(root.itemAt(0))
        }

        if (root.configType === Config.Remote) {
            root.addItem(updateItem.createObject())
        }
        root.addItem(editItem.createObject())
        root.addItem(deleteItem.createObject())
    }

    Component {
        id: updateItem

        MD.MenuItem {
            text: qsTr("Update")
            icon.name: MD.Token.icon.download
            onTriggered: root.updateConfig()
        }
    }

    Component {
        id: editItem

        MD.MenuItem {
            text: qsTr("Edit")
            icon.name: MD.Token.icon.edit
            onTriggered: root.editConfig()
        }
    }

    Component {
        id: deleteItem

        MD.MenuItem {
            text: qsTr("Delete")
            icon.name: MD.Token.icon.delete
            onTriggered: root.deleteConfig()
        }
    }
}
