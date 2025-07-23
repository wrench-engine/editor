#pragma once
#include <cstdint>

namespace wrench_editor {
class IRenderer {
protected:
    IRenderer() = default;

public:
    virtual ~IRenderer() = default;

    virtual double getDeltaTime() const = 0;

    virtual void render() = 0;
};
} // namespace wrench_editor