#include "WrenchEditor.h"
#include "Renderer.h"
#include <wrench_editor/logging/logging.h>
#include <wrench_editor/mvp/view/WrenchEditorCanvas.h>

namespace wrench_editor {
WrenchEditor::WrenchEditor(const Config &config)
    : _config(config) {
    if (!rendell_ui::init()) {
        EDITOR_CRITICAL("Failed to initialize Rendell-UI");
        std::abort();
    }
    _mainWindow = rendell_ui::createWindow(800, 600, "Wrench Editor");
    if (!rendell_ui::isValidWindow(_mainWindow)) {
        EDITOR_CRITICAL("Failed to create main window");
        std::abort();
    }
    _mainWindow->setMinSize({800, 600});

    _viewport = rendell_ui::makeViewport();
    rendell_ui::Viewport::setCurrent(_viewport);

    const auto canvas = makeWrenchEditorCanvas(_viewport);
    canvas->setResizeCallback([&](glm::vec2 size) {
        _frameRate.beginFrame();
        _renderer->render();
        _frameRate.endFrame();
    });
    _canvas = canvas;
    _mainWindow->setEventHandler(_canvas);
    _renderer = make_ref<Renderer>(_viewport);

    _view = make_ref<WrenchEditorView>(_mainWindow, _canvas);
}

WrenchEditor::~WrenchEditor() {
    _view.reset();
    _viewport.reset();
    _renderer.reset();
    _canvas.reset();
    rendell_ui::releaseWindow(_mainWindow);
    rendell_ui::release();
}

int WrenchEditor::run() {
    while (_mainWindow->isOpen()) {
        _frameRate.beginFrame();

        _renderer->render();

        _mainWindow->processEvents();

        _frameRate.endFrame();
        _frameRate.cooldown();

        _mainWindow->waitEvent();
    }
    return 0;
}

} // namespace wrench_editor