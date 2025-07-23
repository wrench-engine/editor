#include <algorithm>
#include <wrench_editor/widgets/ResizableContainerWidget.h>

namespace wrench_editor {
ResizableContainerWidget::ResizableContainerWidget(glm::vec2 minSize, glm::vec2 maxSize)
    : Widget() {
    setMinSize(minSize);
    setMaxSize(maxSize);
}

glm::vec2 ResizableContainerWidget::getMinSize() const {
    return _minSize;
}

glm::vec2 ResizableContainerWidget::getMaxSize() const {
    return _maxSize;
}

void ResizableContainerWidget::setMinSize(glm::vec2 value) {
    value = glm::vec2(std::max(value.x, 0.0f), std::max(value.y, 0.0f));
    if (_minSize != value) {
        _minSize = glm::vec2(std::min(value.x, _maxSize.x), std::min(value.y, _maxSize.y));
        const glm::vec2 newSize{std::max(_size.x, _minSize.x), std::max(_size.y, _minSize.y)};
        setSize(newSize);
    }
}

void ResizableContainerWidget::setMaxSize(glm::vec2 value) {
    value = glm::vec2(std::max(value.x, 0.0f), std::max(value.y, 0.0f));
    if (_maxSize != value) {
        _maxSize = glm::vec2(std::max(_minSize.x, value.x), std::max(_minSize.y, value.y));
        const glm::vec2 newSize{std::min(_size.x, _maxSize.x), std::min(_size.y, _maxSize.y)};
        setSize(newSize);
    }
}

glm::vec2 ResizableContainerWidget::normalizeDelta(glm::vec2 delta) {
    return glm::vec2(std::clamp(_startSize.x + delta.x, _minSize.x, _maxSize.x),
                     std::clamp(_startSize.y + delta.y, _minSize.y, _maxSize.y)) -
           _startSize;
}

bool ResizableContainerWidget::resizeByX(float delta) {
    const float newWidth = std::clamp(_size.x + delta, _minSize.x, _maxSize.x);
    if (newWidth != _size.x) {
        setSize({newWidth, _size.y});
        return true;
    }
    return false;
}

bool ResizableContainerWidget::resizeByY(float delta) {
    const float newHeight = std::clamp(_size.y + delta, _minSize.y, _maxSize.y);
    if (newHeight != _size.y) {
        setSize({_size.x, newHeight});
        return true;
    }
    return false;
}

void ResizableContainerWidget::beginResizing() {
    _startSize = _size;
    _resizeDelta = {};
}

void ResizableContainerWidget::endResizeing() {
}

void ResizableContainerWidget::setResizeDelta(glm::vec2 delta) {
    if (_resizeDelta != delta) {
        _resizeDelta = delta;
        const glm::vec2 newSize{std::clamp(_startSize.x + _resizeDelta.x, _minSize.x, _maxSize.x),
                                std::clamp(_startSize.y + _resizeDelta.y, _minSize.y, _maxSize.y)};
        setSize(newSize);
    }
}

} // namespace wrench_editor
