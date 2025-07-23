#pragma once
#include <rendell_ui/rendell_ui.h>
#include <vector>
//#include <wrench_editor/widgets/DraggablePanelWidget.h>
//#include <wrench_editor/widgets/SplitterWidget.h>

namespace wrench_editor {
class WrenchEditorView final {
public:
    WrenchEditorView(rendell_ui::DockCanvasSharedPtr canvas);
    ~WrenchEditorView() = default;

private:
    rendell_ui::CanvasSharedPtr _canvas;

    rendell_ui::ButtonWidgetSharedPtr _button;

    //DraggablePanelWidgetSharedPtr _draggablePanelWidget;
    //std::vector<SplitterWidgetSharedPtr> _splitters;
};
} // namespace wrench_editor