import QtQuick

import Qcm.Material as MD
import QtQuick.Controls

MD.Button {
    id: control

    icon.name: MD.Token.icon.add
    text: qsTr("Add new profile")
    mdState: MD.StateButton {
            item: control
            backgroundColor: "transparent"
            textColor: MD.Token.color.on_secondary_container
    }

    AddProfileDialog {
        id: addProfileDialog

        anchors.centerIn: Overlay.overlay
        parent: Overlay.overlay

        onAccepted: {
            console.log("Profile added:")
        }
    }

    onClicked: {
        addProfileDialog.open()
    }
}
