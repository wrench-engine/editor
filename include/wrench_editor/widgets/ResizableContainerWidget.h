#pragma once
#include <rendell_ui/rendell_ui.h>

namespace wrench_editor {
class ResizableContainerWidget : public rendell_ui::Widget {
public:
    ResizableContainerWidget(glm::vec2 minSize = {}, glm::vec2 maxSize = {500.0f, 500.0f});
    virtual ~ResizableContainerWidget() = default;

    glm::vec2 getMinSize() const;
    glm::vec2 getMaxSize() const;

    void setMinSize(glm::vec2 value);
    void setMaxSize(glm::vec2 value);

    glm::vec2 normalizeDelta(glm::vec2 delta);

    bool resizeByX(float delta);
    bool resizeByY(float delta);

    void beginResizing();
    void endResizeing();
    void setResizeDelta(glm::vec2 delta);

private:
    glm::vec2 _minSize;
    glm::vec2 _maxSize;
    glm::vec2 _startSize{};
    glm::vec2 _resizeDelta{};
};

RENDELL_UI_DECLARE_WIDGET(ResizableContainerWidget)
} // namespace wrench_editor