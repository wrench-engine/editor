#include <wrench_editor/mvp/view/WrenchEditorView.h>

#define BACKGROUND_COLOR {0.12f, 0.12f, 0.12f, 1.0f}
#define SPLITTER_COLOR {0.18f, 0.18f, 0.18f, 1.0f}

namespace wrench_editor {
static rendell_ui::DockSeparatorSharedPtr createDockSeparator(rendell_ui::WidgetSharedPtr parent) {
    const auto result = rendell_ui::createDockSeparator(parent);
    result->setColor(SPLITTER_COLOR);
    return result;
}

static rendell_ui::WidgetSharedPtr
createDockNodeBackgroundWidget(rendell_ui::WidgetSharedPtr parent, const glm::vec4 color) {
    const auto result = rendell_ui::createRectangleWidget(parent);
    result->setAnchor(rendell_ui::Anchor::centerStretch);
    result->setColor(color);
    return result;
}
} // namespace wrench_editor

namespace wrench_editor {
WrenchEditorView::WrenchEditorView(rendell_ui::DockCanvasSharedPtr canvas)
    : _canvas(canvas) {
    rendell_ui::DockNode::setCreateDockSeparatorCallback(createDockSeparator);

    // Viewport
    const auto viewportDockNode = rendell_ui::makeDockNode(nullptr, _canvas->getRootWidget());
    createDockNodeBackgroundWidget(viewportDockNode->getRootWidget(), BACKGROUND_COLOR);
    canvas->setRootDockNode(viewportDockNode);

    // Inspector
    const auto inspectorDockNode =
        rendell_ui::makeDockNode(viewportDockNode, _canvas->getRootWidget());
    createDockNodeBackgroundWidget(inspectorDockNode->getRootWidget(), RENDELL_UI_RED_COLOR);
    viewportDockNode->splitBy(inspectorDockNode, rendell_ui::DockNode::SplitType::right);

    // File browser
    const auto fileBrowserDockNode =
        rendell_ui::makeDockNode(inspectorDockNode, _canvas->getRootWidget());
    createDockNodeBackgroundWidget(fileBrowserDockNode->getRootWidget(), RENDELL_UI_GREEN_COLOR);
    inspectorDockNode->splitBy(fileBrowserDockNode, rendell_ui::DockNode::SplitType::bottom);
}

} // namespace wrench_editor