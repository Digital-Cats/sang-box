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

    CheckBox {
        id: checkBox

        implicitHeight: 24
        implicitWidth: 24

        Material.theme: Material.Dark
        Material.accent: MD.Token.color.primary_container
        Material.foreground: MD.Token.color.outline

        onClicked: {
            root.clicked()
        }
    }


    Label {
        id: label

        color: MD.Token.color.on_secondary_container
        font.pixelSize: 16
        Layout.leftMargin: 5
        font.weight: 600
    }
}
