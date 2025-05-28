import QtQuick

import Qcm.Material as MD

MD.Button {
    id: control

    icon.name: MD.Token.icon.add
    text: qsTr("Add new profile")
    mdState: MD.StateButton {
            item: control
            backgroundColor: "transparent"
            textColor: MD.Token.color.on_secondary_container
    }
}
