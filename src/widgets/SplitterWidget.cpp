#include <algorithm>
#include <wrench_editor/logging/logging.h>
#include <wrench_editor/widgets/SplitterWidget.h>

namespace wrench_editor {
SplitterWidget::SplitterWidget()
    : rendell_ui::RectangleWidget() {
    update();
}

void SplitterWidget::onMouseDown(glm::dvec2 cursorPosition) {
}

void SplitterWidget::onMouseEntered() {
    const auto windowCursorType = _type == Type::horizontal
                                      ? rendell_ui::WindowCursorType::verticalResize
                                      : rendell_ui::WindowCursorType::horizontalResize;
    setWindowCursorType(windowCursorType);
}

void SplitterWidget::onMouseExited() {
    setWindowCursorType(rendell_ui::WindowCursorType::arrow);
}

void SplitterWidget::onCaptured(glm::dvec2 cursorPosition) {
    _startOffset = _offset;
    if (_firstBindedWidget) {
        _firstBindedWidget->beginResizing();
    }
    if (_secondBindedWidget) {
        _secondBindedWidget->beginResizing();
    }
}

void SplitterWidget::onDragged(glm::dvec2 startPoint, glm::dvec2 endPoint) {
    const glm::vec2 dragDelta = static_cast<glm::vec2>(endPoint - startPoint);
    const glm::vec2 delta =
        _type == Type::horizontal ? glm::vec2(0.0f, dragDelta.y) : glm::vec2(dragDelta.x, 0.0f);

    glm::vec2 firstDelta = delta;
    if (_firstBindedWidget) {
        firstDelta = _firstBindedWidget->normalizeDelta(delta);
    }
    glm::vec2 secondDelta = delta;
    if (_secondBindedWidget) {
        secondDelta = _secondBindedWidget->normalizeDelta(delta);
    }
    const glm::vec2 bestDelta =
        glm::dot(firstDelta, firstDelta) > glm::dot(secondDelta, secondDelta) ? secondDelta
                                                                              : firstDelta;
    if (_firstBindedWidget) {
        _firstBindedWidget->setResizeDelta(bestDelta);
    }
    if (_secondBindedWidget) {
        _secondBindedWidget->setResizeDelta(bestDelta);
    }

    setOffset(_startOffset + bestDelta);
}

SplitterWidget::Type SplitterWidget::getType() const {
    return _type;
}

rendell_ui::WidgetSharedPtr SplitterWidget::getFirstBindedWidget() const {
    return _firstBindedWidget;
}
rendell_ui::WidgetSharedPtr SplitterWidget::getSecondBindedWidget() const {
    return _secondBindedWidget;
}

void SplitterWidget::setFirstResizableContainerWidget(
    ResizableContainerWidgetSharedPtr firstWidget) {
    if (_firstBindedWidget != firstWidget) {
        _firstBindedWidget = firstWidget;
        update();
    }
}

void SplitterWidget::setSecondResizableContainerWidget(
    ResizableContainerWidgetSharedPtr secondWidget) {
    if (_secondBindedWidget != secondWidget) {
        _secondBindedWidget = secondWidget;
        update();
    }
}

void SplitterWidget::setType(Type type) {
    if (_type != type) {
        _type = type;
        update();
    }
}

void SplitterWidget::update() {
    float width;
    float height;
    glm::vec2 offset;

    const auto firstSize =
        _firstBindedWidget ? _firstBindedWidget->getSize() : glm::vec2(0.0f, 0.0f);
    const auto secondSize =
        _secondBindedWidget ? _secondBindedWidget->getSize() : glm::vec2(0.0f, 0.0f);

    if (_type == Type::vertical) {
        width = std::max(firstSize.x, secondSize.x);
        height = std::max(firstSize.y, secondSize.y);
        offset = glm::vec2(firstSize.x + secondSize.x) * 0.5f;
    } else {
        width = std::max(firstSize.y, secondSize.y);
        height = std::max(firstSize.x, secondSize.x);
        offset = glm::vec2(firstSize.y + secondSize.y) * 0.5f;
    }

    setAnchor(rendell_ui::Anchor::center);
    setColor(RENDELL_UI_RED_COLOR);
    setSize(glm::vec2(width, height));
}

} // namespace wrench_editor