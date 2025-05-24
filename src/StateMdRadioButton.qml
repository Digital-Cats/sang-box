import QtQuick
import Qcm.Material as MD

MD.State {
    id: root

    stateLayerColor: root.item.checked ? root.ctx.color.primary : root.ctx.color.on_surface_variant
}
