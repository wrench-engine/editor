#pragma once
#include <memory>

namespace wrench_editor {
template <typename T> using Ref = std::shared_ptr<T>;

template <typename T, typename... Args> Ref<T> make_ref(Args &&...args) {
    return Ref<T>(std::make_shared<T>(std::forward<Args>(args)...));
}
} // namespace wrench_editor