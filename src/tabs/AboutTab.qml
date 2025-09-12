import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qcm.Material as MD

import "../controls"

BasicTab {
    id: root

    property string linkCss:
        "<style>a, a:link, a:visited { " +
        "text-decoration: none; font-weight: 700; " +
        "color: " + MD.Token.color.on_secondary_container + "; }</style>"

    contentItem: Item {
        ControlCard {
            id: aboutMenu
            anchors.fill: parent
            labelText: qsTr("About sang-box")
            anchors.bottomMargin: 200

            contentItem: Item {
                anchors.top: parent.header.bottom
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.leftMargin: 16
                anchors.topMargin: 16

                ColumnLayout {
                    spacing: 16
                    anchors.fill: parent

                    RichLinkIconText {
                        content: qsTr("sang-box is an unofficial GUI app for the proxy platform called %1")
                        linkUrl: "https://sing-box.sagernet.org"
                        linkText: "sing-box"
                        linkDecoration: "underline"
                        iconOnLeft: false
                        iconName: MD.Token.icon.open_in_new
                    }

                    RichLinkAvatarText {
                        content: qsTr("<b>sing-box</b> is developed by %1")
                        linkUrl: "https://github.com/SagerNet"
                        linkText: "SagerNet"
                        linkWeight: 400
                        avatarUrl: "https://github.com/SagerNet.png?size=24"
                        avatarOnLeft: true
                        avatarCircle: true
                        avatarSize: 24
                    }

                    RichLinkImageText {
                        content: qsTr("<b>sing-box</b> documentation is avalaible at %1")
                        linkUrl: "https://sing-box.sagernet.org/"
                        linkText: "sing-box.sagernet.org"
                        linkWeight: 400
                        imageUrl: "https://sing-box.sagernet.org/assets/icon.svg"
                        imageOnLeft: true
                        imageWidth: 24
                        imageHeight: 24
                        imageGap: 2
                    }

                    RowLayout {
                        spacing: 4

                        RichLinkAvatarText {
                            content: qsTr("<b>this app</b> is developed by %1")
                            linkUrl: "https://github.com/Roker2"
                            linkText: "Roker2"
                            linkWeight: 400
                            avatarUrl: "https://github.com/Roker2.png?size=24"
                            avatarOnLeft: true
                            avatarCircle: true
                            avatarSize: 24
                        }

                        RichLinkAvatarText {
                            content: qsTr("and %1,")
                            linkUrl: "https://github.com/L4zzur"
                            linkText: "L4zzur"
                            linkWeight: 400
                            avatarUrl: "https://github.com/L4zzur.png?size=24"
                            avatarOnLeft: true
                            avatarCircle: true
                            avatarSize: 24
                        }

                        RichLinkAvatarText {
                            content: qsTr("CI/CD by %1")
                            linkUrl: "https://github.com/Korsilyn"
                            linkText: "Korsilyn"
                            linkWeight: 400
                            avatarUrl: "https://github.com/Korsilyn.png?size=24"
                            avatarOnLeft: true
                            avatarCircle: true
                            avatarSize: 24
                        }
                    }

                    RowLayout {
                        Layout.leftMargin: 92

                        RichLinkAvatarText {
                            content: qsTr("designed by %1,")
                            linkUrl: "https://github.com/vulpeace"
                            linkText: "vulpeace"
                            linkWeight: 400
                            avatarUrl: "https://github.com/vulpeace.png?size=24"
                            avatarOnLeft: true
                            avatarCircle: true
                            avatarSize: 24
                        }

                        RichLinkAvatarText {
                            content: qsTr("tested by %1")
                            linkUrl: "https://github.com/Invertify"
                            linkText: "Invertify"
                            linkWeight: 400
                            avatarUrl: "https://github.com/Invertify.png?size=24"
                            avatarOnLeft: true
                            avatarCircle: true
                            avatarSize: 24
                        }
                    }

                    RichLinkAvatarText {
                        content: qsTr("source code is avalaible at %1")
                        linkUrl: "https://github.com/Digital-Cats/sang-box/"
                        linkText: "Digital-Cats/sang-box"
                        linkWeight: 400
                        avatarUrl: "https://sing-box.sagernet.org/assets/icon.svg"
                        avatarOnLeft: true
                        avatarCircle: false
                        avatarSize: 24
                        spacing: 3
                    }

                    RichLinkAvatarText {
                        content: qsTr("original idea by %1")
                        linkUrl: "https://github.com/nextincn/qsing-box"
                        linkText: "nextincn/qsing-box"
                        linkWeight: 400
                        avatarUrl: "https://github.com/nextincn.png?size=24"
                        avatarOnLeft: true
                        avatarCircle: true
                        avatarSize: 24
                    }

                    RichLinkImageText {
                        content: "build using %1 " +
                                 mainWindow.updater.qtVersion +
                                 " (MinGW " + mainWindow.updater.compilerVersion +
                                 ") on " + mainWindow.updater.buildTime
                        linkUrl: "https://www.qt.io/"
                        linkText: "Qt"
                        linkWeight: 400

                        imageUrl: "https://www.qt.io/hs-fs/hubfs/Qt-logo-neon_900px.png?width=300&height=214&name=Qt-logo-neon_900px.png"
                        imageOnLeft: true
                        imageWidth: 24
                        imageHeight: 18
                    }

                    RichLinkAvatarText {
                        content: qsTr("user interface via %1")
                        linkUrl: "https://github.com/hypengw/QmlMaterial"
                        linkText: "hypengw/QmlMaterial"
                        linkWeight: 400
                        avatarUrl: "https://github.com/hypengw.png?size=24"
                        avatarOnLeft: true
                        avatarCircle: false
                        avatarSize: 24
                    }

                    Item {
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }
}
