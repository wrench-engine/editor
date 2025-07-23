#pragma once
#include <rendell_ui/rendell_ui.h>

namespace wrench_editor {
class Window {
public:
    Window();
    virtual ~Window();

protected:
    rendell_ui::WindowSharedPtr _window;
};
} // namespace wrench_editor
