import QtQuick
import QtQuick.Controls.Material
import MMaterial

import Qcm.Material as MD

Window {
    width: 1000
    height: 750
	visible: true
	color: Theme.background.main
    title: qsTr("sang-box")

    minimumWidth: 1000
    minimumHeight: 750
    maximumWidth: 1000
    maximumHeight: 750

	MainWindowView {
		anchors.fill: parent
	}

    Connections {
        target: trayIcon

        function onOpenWindowTriggered() {
            show()
        }

        function onRestoreActionTriggered() {
            show()
        }
    }

    Component.onCompleted: {
        MD.Token.color.paletteType = 2
        MD.Token.color.useSysColorSM = false;
        MD.Token.themeMode = MD.Enum.Dark
        MD.Token.color.accentColor = "#F6F4B7";
    }

    onClosing: function(close) {
        close.accepted = false
        hide()
    }
}
