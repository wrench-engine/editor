#pragma once
#include "Config.h"
#include "FrameRate.h"
#include <rendell_ui/rendell_ui.h>
#include <wrench_editor/IRenderer.h>
#include <wrench_editor/mvp/view/WrenchEditorView.h>
#include <wrench_editor/memory/Ref.h>

namespace wrench_editor {
class WrenchEditor final {
public:
    WrenchEditor(const Config &config);
    ~WrenchEditor() = default;

    int run();

private:
    Config _config;
    FrameRate _frameRate{};
    rendell_ui::WindowSharedPtr _mainWindow;
    rendell_ui::ViewportSharedPtr _viewport;
    rendell_ui::DockCanvasSharedPtr _canvas;
    Ref<IRenderer> _renderer;

    Ref<WrenchEditorView> _view;
};
} // namespace wrench_editor
