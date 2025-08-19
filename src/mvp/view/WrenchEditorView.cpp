#include <wrench_editor/mvp/view/WrenchEditorView.h>

#define BACKGROUND_COLOR {0.12f, 0.12f, 0.12f, 1.0f}
#define SPLITTER_COLOR {0.18f, 0.18f, 0.18f, 1.0f}

namespace wrench_editor {
static rendell_ui::DockSeparatorWidgetSharedPtr
createDockSeparator(rendell_ui::WidgetSharedPtr parent) {
    const auto result = rendell_ui::createDockSeparatorWidget(parent);
    result->setColor(SPLITTER_COLOR);
    return result;
}

static rendell_ui::WidgetSharedPtr
createDockNodeBackgroundWidget(rendell_ui::WidgetSharedPtr parent, const glm::vec4 color) {
    const auto result = rendell_ui::createRectangleWidget(parent);
    result->setName("WRENCH_EDITOR");
    result->setAnchor(rendell_ui::Anchor::centerStretch);
    // result->setAnchor(rendell_ui::Anchor::center);
    result->setColor(color);
    return result;
}
} // namespace wrench_editor

namespace wrench_editor {
WrenchEditorView::WrenchEditorView(rendell_ui::IWindowWeakPtr window,
                                   rendell_ui::DockCanvasSharedPtr canvas)
    : _canvas(canvas) {
    const rendell_ui::WidgetSharedPtr canvasRootWidget = canvas->getRootWidget();

    // Viewport
    auto viewportDockableWindow = rendell_ui::makeDockableWindow("Viewport", canvasRootWidget);
    createDockNodeBackgroundWidget(viewportDockableWindow->getWorkSpaceWidget(), BACKGROUND_COLOR);
    viewportDockableWindow->setMinSize({200.0f, 200.0f});

    // Inspector
    auto inspectorDockableWindow = rendell_ui::makeDockableWindow("Inspector", canvasRootWidget);
    createDockNodeBackgroundWidget(inspectorDockableWindow->getWorkSpaceWidget(), BACKGROUND_COLOR);
    inspectorDockableWindow->setMinSize({200.0f, 200.0f});

    // File browser
    auto fileBrowserDockableWindow =
        rendell_ui::makeDockableWindow("File browser", canvasRootWidget);
    createDockNodeBackgroundWidget(fileBrowserDockableWindow->getWorkSpaceWidget(),
                                   BACKGROUND_COLOR);
    fileBrowserDockableWindow->setMinSize({200.0f, 200.0f});

    // Tree
    auto treeDockableWindow = rendell_ui::makeDockableWindow("Tree", canvasRootWidget);
    createDockNodeBackgroundWidget(treeDockableWindow->getWorkSpaceWidget(), BACKGROUND_COLOR);
    treeDockableWindow->setMinSize({200.0f, 200.0f});

    _dockTree = rendell_ui::DockTreeBuilder(canvasRootWidget)
                    .setWindow(window)
                    .setCreateSeparatorDelegate(createDockSeparator)
                    .splitVertical()
                    .goFirst()
                    .splitHorizontal()
                    .goFirst()
                    .setDockable(fileBrowserDockableWindow)
                    .goParent()
                    .goSecond()
                    .splitVertical()
                    .goFirst()
                    .setDockable(viewportDockableWindow)
                    .goParent()
                    .goSecond()
                    .setDockable(treeDockableWindow)
                    .goRoot()
                    .goSecond()
                    .setDockable(inspectorDockableWindow)
                    .build();

    canvas->setRootDockNode(_dockTree->getRootNode());

    /*
    Node (vertical)
        Node (horizontal)
            Node (container)
                File browser
            Node (vertical)
                Node (Container)
                    Viewport
                Node (Container)
                    Tree
        Node (container)
            Inspector
    */
}

} // namespace wrench_editor