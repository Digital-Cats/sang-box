import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

import Qcm.Material as MD

RowLayout {
    id: root

    property alias labelText: label.text
    property alias labelColor: label.color
    property alias checked: checkBox.checked
    signal clicked

    MD.CheckBox {
        id: checkBox

        Material.theme: Material.Dark
        Material.accent: MD.Token.color.primary_container
        Material.foreground: MD.Token.color.outline

        onClicked: {
            root.clicked()
        }
    }


    MD.Label {
        id: label

        color: MD.Token.color.on_secondary_container
        Layout.leftMargin: 4
        typescale: MD.Token.typescale.body_large
    }
}
