import QtQuick
import QtQuick.Controls.Material

import Qcm.Material as MD

ApplicationWindow {
    id: root

    property bool allowToClose: false

    width: 1000
    height: 750
    visible: true
    title: qsTr("sang-box")

    minimumWidth: 916
    minimumHeight: 750
    maximumWidth: 1000
    maximumHeight: 750

    FontLoader {
        id: notoSans
        source: "qrc:/fonts/NotoSans-VariableFont_wdth,wght.ttf"
    }

    font.family: notoSans.name

	MainWindowView {
		anchors.fill: parent
	}

    Shortcut {
        enabled: underhood.isDebug
        sequence: "F5"
        onActivated: {
            root.allowToClose = true
            root.close()
            underhood.invokedReloadSrcQml()
        }
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
        if (!root.allowToClose) {
            close.accepted = false
            hide()
        }
    }
}
