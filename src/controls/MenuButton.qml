import QtQuick
import QtQuick.Layouts
import QtQuick.Templates as T
import Qcm.Material as MD

T.Button {
    id: control

    property alias mdState: m_sh.state

    icon.width: 18
    icon.height: 18

    contentItem: Item {
        anchors.centerIn: parent

        RowLayout {
            anchors.centerIn: parent

            spacing: 8

            MD.Icon {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: control.icon.width
                Layout.preferredHeight: control.icon.width
                name: control.icon.name
                size: control.icon.width
                color: control.mdState.supportTextColor
                fill: control.checked
            }

            MD.Text {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                opacity: {
                    const left = 0.2;
                    const right = 0.8;
                    const w = control.range;
                    return MD.Util.teleportCurve(w, left, right);
                }
                typescale: MD.Token.typescale.title_medium
                font.capitalization: Font.Capitalize
                text: control.text
                prominent: control.checked
                color: control.mdState.textColor
            }
        }
    }

    background: Rectangle {
        anchors.fill: parent

        border.width: 1
        border.color: control.checked ? MD.Token.color.outline : "transparent"
        topRightRadius: 100
        bottomRightRadius: 100
        color: control.mdState.backgroundColor
    }

    MD.StateHolder {
        id: m_sh
        state: MD.StateRailItem {
            item: control
        }
    }
}
