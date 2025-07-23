#pragma once
#include <rendell_ui/rendell_ui.h>
#include <wrench_editor/widgets/ResizableContainerWidget.h>

namespace wrench_editor {
class SplitterWidget : public rendell_ui::RectangleWidget {
public:
    enum class Type {
        horizontal,
        vertical,
    };

    SplitterWidget();
    virtual ~SplitterWidget() = default;

    // Widget
    void onMouseDown(glm::dvec2 cursorPosition) override;
    void onMouseEntered() override;
    void onMouseExited() override;
    void onCaptured(glm::dvec2 cursorPosition) override;
    void onDragged(glm::dvec2 startPoint, glm::dvec2 endPoint) override;

    Type getType() const;
    rendell_ui::WidgetSharedPtr getFirstBindedWidget() const;
    rendell_ui::WidgetSharedPtr getSecondBindedWidget() const;

    void setType(Type type);
    void setFirstResizableContainerWidget(ResizableContainerWidgetSharedPtr firstWidget);
    void setSecondResizableContainerWidget(ResizableContainerWidgetSharedPtr secondWidget);

protected:
    void update();

    Type _type{Type::vertical};
    ResizableContainerWidgetSharedPtr _firstBindedWidget{nullptr};
    ResizableContainerWidgetSharedPtr _secondBindedWidget{nullptr};
    glm::vec2 _startOffset{};
    bool _isCaptured{false};
};

RENDELL_UI_DECLARE_WIDGET(SplitterWidget)
} // namespace wrench_editor