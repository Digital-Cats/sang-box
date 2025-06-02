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

        implicitHeight: 22
        implicitWidth: 22

        onClicked: {
            root.clicked()
        }
    }

    Label { id: label; font.pixelSize: 16; Layout.leftMargin: 12; font.weight: 600 }
}
