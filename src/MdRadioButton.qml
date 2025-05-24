import QtQuick
import QtQuick.Templates as T

import Qcm.Material as MD

T.RadioButton {
    id: control

    property color color: mdState.stateLayerColor
    property alias mdState: m_sh.state

    implicitHeight: 48
    implicitWidth: 48

    Rectangle {
        id: borderCircle

        anchors.centerIn: parent

        height: 20
        width: 20
        color: "transparent"
        radius: 100
        border {
            width: 2
            color: control.color
        }
    }

    Rectangle {
        id: innerCircle

        anchors.fill: borderCircle
        anchors.margins: borderCircle.height * 0.25
        radius: 100
        color: control.color
    }

    states: [
        State {
            when: control.checked
            name: "Checked"
            PropertyChanges { target: innerCircle; visible: true }
        },
        State {
            when: true
            name: "Unchecked"
            PropertyChanges { target: innerCircle; visible: false }
        }
    ]

    MD.StateHolder {
        id: m_sh
        state: StateMdRadioButton {
            item: control
        }
    }
}
