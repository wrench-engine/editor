#pragma once
#include <rendell_ui/rendell_ui.h>
#include <vector>

namespace wrench_editor {
class WrenchEditorView final {
public:
    WrenchEditorView(rendell_ui::IWindowWeakPtr window, rendell_ui::DockCanvasSharedPtr canvas);
    ~WrenchEditorView() = default;

private:
    rendell_ui::CanvasSharedPtr _canvas;
    rendell_ui::DockTreeSharedPtr _dockTree;

    rendell_ui::ButtonWidgetSharedPtr _button;
};
} // namespace wrench_editor