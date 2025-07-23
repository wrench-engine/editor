#pragma once
#include <rendell_ui/rendell_ui.h>
#include "ResizableContainerWidget.h"

namespace wrench_editor {
class DraggablePanelWidget final : public ResizableContainerWidget {
public:
    enum class Side {
        left,
        right,
        bottom,
        top,
    };

    DraggablePanelWidget(glm::vec2 minSize = {}, glm::vec2 maxSize = {500.0f, 500.0f});
    ~DraggablePanelWidget() = default;

    Side getSide() const;

    void setSide(Side side);

private:
    void onSelfWeakPtrChanged() override;
    rendell_ui::Anchor getAnchorBySide(Side side) const;
    void updateSideAnchor();

    rendell_ui::RectangleWidgetSharedPtr _backgroundWidget;
    Side _side;
};

RENDELL_UI_DECLARE_WIDGET(DraggablePanelWidget)
} // namespace wrench_editor