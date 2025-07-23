#pragma once
#include <functional>
#include <rendell_ui/rendell_ui.h>

namespace wrench_editor {
class WrenchEditorCanvas final : public rendell_ui::DockCanvas {
public:
    using ResizeCallback = std::function<void(glm::vec2 size)>;

    WrenchEditorCanvas(rendell_ui::ViewportSharedPtr viewport);
    ~WrenchEditorCanvas() = default;

    ResizeCallback getResizeCallback() const;

    void setResizeCallback(ResizeCallback callback);

private:
    void onResized(glm::ivec2 size) override;

    ResizeCallback _resizeCallback{nullptr};
};
RENDELL_UI_DECLARE_SHARED_PTR_FACTORY(WrenchEditorCanvas)

} // namespace wrench_editor