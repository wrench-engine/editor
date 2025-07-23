#include "FrameRate.h"
#include <wrench_editor/utils/sleep.h>

namespace wrench_editor {
FrameRate::FrameRate(uint32_t fpsLimit) {
    setFpsLimit(fpsLimit);
}

uint32_t FrameRate::getFps() const {
    return _fps;
}

uint32_t FrameRate::getFpsLimit() const {
    return _fpsLimit;
}

double FrameRate::getDeltaTime() const {
    return _deltaTime;
}

void FrameRate::setFpsLimit(uint32_t limit) {
    if (limit == 0) {
        return;
    }
    _fpsLimit = limit;
    _targetFrameTime = 1.0 / _fpsLimit;
}

void FrameRate::beginFrame() {
    _frameStartTimePoint = Clock::now();
}

void FrameRate::endFrame() {
    _frameEndTimePoint = Clock::now();
    _deltaTime = std::chrono::duration<double>(_frameEndTimePoint - _frameStartTimePoint).count();
    _sleepTime = _targetFrameTime - _deltaTime;
    _fps = static_cast<int>(1.0 / (_deltaTime + _sleepTime));
}

void FrameRate::cooldown() {
    if (_sleepTime > 0) {
        sleep_microseconds(static_cast<long long>(_sleepTime * 1000000.0));
    }
}

} // namespace wrench_editor