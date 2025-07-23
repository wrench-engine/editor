#include <wrench_editor/mvp/view/WrenchEditorCanvas.h>

namespace wrench_editor {

WrenchEditorCanvas::WrenchEditorCanvas(rendell_ui::ViewportSharedPtr viewport)
    : rendell_ui::DockCanvas(viewport) {
}

WrenchEditorCanvas::ResizeCallback WrenchEditorCanvas::getResizeCallback() const {
    return _resizeCallback;
}

void WrenchEditorCanvas::setResizeCallback(ResizeCallback callback) {
    _resizeCallback = callback;
}

void WrenchEditorCanvas::onResized(glm::ivec2 size) {
    rendell_ui::DockCanvas::onResized(size);
    if (_resizeCallback) {
        _resizeCallback(size);
    }
}
} // namespace wrench_editor