import QtQuick

import Qcm.Material as MD

MD.FAB {
    id: control
    type: MD.Enum.FABLarge

    icon.name: control.checked ?
                   MD.Token.icon.pause :
                   MD.Token.icon.play_arrow
    icon.width: 36
    icon.height: 36

    mdState: MD.StateFAB {
        backgroundColor: control.checked ?
                             MD.Token.color.primary_container :
                             MD.Token.color.surface_container_high
        textColor: control.checked ?
                       MD.Token.color.on_primary_container :
                       MD.Token.color.primary
        item: control
    }
}
