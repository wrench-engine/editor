#include <wrench_editor/widgets/DraggablePanelWidget.h>

namespace wrench_editor {
DraggablePanelWidget::DraggablePanelWidget(glm::vec2 minSize, glm::vec2 maxSize)
    : ResizableContainerWidget(minSize, maxSize) {
    setSide(_side);
    _backgroundWidget = rendell_ui::createRectangleWidget();
    _backgroundWidget->setAnchor(rendell_ui::Anchor::centerStretch);
}

void DraggablePanelWidget::onSelfWeakPtrChanged() {
    _backgroundWidget->setParent(_selfWeakPtr);
    // setAnchor(rendell_ui::Anchor::centerStretch);
}

DraggablePanelWidget::Side DraggablePanelWidget::getSide() const {
    return _side;
}

void DraggablePanelWidget::setSide(Side side) {
    if (_side != side) {
        _side = side;
        updateSideAnchor();
    }
}

rendell_ui::Anchor DraggablePanelWidget::getAnchorBySide(Side side) const {
    switch (side) {
    case Side::left:
        return rendell_ui::Anchor::leftStretch;
    case Side::right:
        return rendell_ui::Anchor::rightStretch;
    case Side::bottom:
        return rendell_ui::Anchor::bottomStretch;
    case Side::top:
        return rendell_ui::Anchor::topStretch;
    }
    return rendell_ui::Anchor::leftStretch;
}

void DraggablePanelWidget::updateSideAnchor() {
    const rendell_ui::Anchor anchor = getAnchorBySide(_side);
    setAnchor(anchor);
}

} // namespace wrench_editor