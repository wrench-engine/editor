#pragma once
#include <wrench_editor/IRenderer.h>
#include <cstdint>
#include <rendell_ui/rendell_ui.h>

namespace wrench_editor {
class Renderer final : public IRenderer {
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

public:
    Renderer(rendell_ui::ViewportSharedPtr viewport);
    ~Renderer();

    double getDeltaTime() const override;

    void render() override;

private:
    void startRenderer();
    void endRenderer();

    rendell_ui::ViewportSharedPtr _viewport;

    TimePoint _frameStartTimePoint{};
    TimePoint _frameEndTimePoint{};
    double _deltaTime{};
};

} // namespace wrench_editor