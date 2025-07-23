#include <rendell_ui/rendell_ui.h>
#include "Renderer.h"

namespace wrench_editor {
Renderer::Renderer(rendell_ui::ViewportSharedPtr viewport)
    : _viewport(viewport) {
}

Renderer::~Renderer() {
}

double Renderer::getDeltaTime() const {
    return _deltaTime;
}

void Renderer::render() {
    startRenderer();

    _viewport->apply();

    rendell::clear();
    rendell::clearColor(0.0f, 0.0f, 0.0f, 1);

    rendell_ui::draw();

    rendell::swapBuffers();

    endRenderer();
}

void Renderer::startRenderer() {
    rendell_ui::Viewport::setCurrent(_viewport);
    rendell_ui::startFrame();

    _frameStartTimePoint = Clock::now();
}

void Renderer::endRenderer() {
    rendell_ui::endFrame();

    _frameEndTimePoint = Clock::now();
    _deltaTime = std::chrono::duration<double>(_frameEndTimePoint - _frameStartTimePoint).count();
}

} // namespace wrench_editor