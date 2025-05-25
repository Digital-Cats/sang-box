import QtQuick
import QtQuick.Controls.Material as QMD
import QtQuick.Layouts
import MMaterial

import Qcm.Material as MD

import "controls"

ControlMenu {
    id: root

    property var model
    property color fontColor
    property int fontSize: root.typescale.size

    QMD.ScrollView {
        Layout.fillWidth: true
        Layout.fillHeight: true
        anchors.top: parent.horizontalLine.bottom
        anchors.topMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 16
        spacing: 15

        ListView {
            id: profilesList

            anchors.fill: parent
            model: root.model

            delegate: RowLayout {
                width: parent.width

                MdRadioButton {
                    checked: model.selected
                    onClicked: {
                        root.model.switchConfig(index)
                    }
                }

                MD.Label {
                    text: model.name
                    typescale: root.typescale
                    color: root.fontColor
                }

                Item {
                    Layout.fillWidth: true
                }

                MButton {
                    accent: Theme.passive
                    type: MButton.Type.Text
                    text: ""
                    leftIcon.iconData: Icons.light.moreVert
                    leftIcon.size: Size.pixel20
                    implicitHeight: 40
                    implicitWidth: 40
                    radius: 100

                    onClicked: {
                        configMenu.popup()
                    }
                }

                Menu {
                    id: configMenu
                    implicitWidth: 120
                    implicitHeight: 120

                    MenuItem {
                        text: qsTr("Update")
                        font.pixelSize: root.fontSize;
                        iconData: Icons.light.download
                        icon.height: Size.pixel16
                        icon.width: Size.pixel16
                    }

                    MenuItem {
                        text: qsTr("Edit")
                        font.pixelSize: root.fontSize;
                        iconData: Icons.light.edit
                        icon.height: Size.pixel16
                        icon.width: Size.pixel16

                        onClicked: model.editConfig(index)
                    }

                    MenuItem {
                        text: qsTr("Delete")
                        font.pixelSize: root.fontSize;
                        iconData: Icons.light.deleteElement
                        icon.height: Size.pixel16
                        icon.width: Size.pixel16

                        onClicked: model.deleteConfig(index)
                    }
                }
            }
        }

        MButton {
            y: profilesList.contentHeight
            width: parent.width
            accent: Theme.passive
            type: MButton.Type.Text
            text: qsTr("Add new profile")
            leftIcon.iconData: Icons.light.add
            leftIcon.size: Size.pixel20
            radius: 100

            onClicked: {
                model.importConfig()
            }
        }
    }
}
