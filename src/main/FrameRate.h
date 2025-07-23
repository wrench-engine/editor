#pragma once
#include <chrono>
#include <cstdint>

namespace wrench_editor {
class FrameRate final {
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

public:
    FrameRate(uint32_t fpsLimit = 60);
    ~FrameRate() = default;

    uint32_t getFps() const;
    uint32_t getFpsLimit() const;
    double getDeltaTime() const;

    void setFpsLimit(uint32_t limit);

    void beginFrame();
    void endFrame();
    void cooldown();

    uint32_t _fps{0};
    uint32_t _fpsLimit{60};
    double _targetFrameTime{1.0 / _fpsLimit};

    TimePoint _frameStartTimePoint{};
    TimePoint _frameEndTimePoint{};
    double _deltaTime{};
    double _sleepTime{};
};
} // namespace wrench_editor
