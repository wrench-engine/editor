#pragma once
#include <format>
#include <logx/logx.h>

namespace wrench_editor {
class WrenchEditorLogger final : public logx::Logger {
public:
    WrenchEditorLogger();
    ~WrenchEditorLogger() = default;

private:
    const char *getLevelName_Unsafe(logx::Level level) const override;
};

logx::Logger *get_logger();

} // namespace wrench_editor

#define EDITOR_CRITICAL(formatStr, ...)                                                            \
    wrench_editor::get_logger()->critical(std::format(formatStr, ##__VA_ARGS__))
#define EDITOR_ERROR(formatStr, ...)                                                               \
    wrench_editor::get_logger()->error(std::format(formatStr, ##__VA_ARGS__))
#define EDITOR_WARNING(formatStr, ...)                                                             \
    wrench_editor::get_logger()->warning(std::format(formatStr, ##__VA_ARGS__))
#define EDITOR_INFO(formatStr, ...)                                                                \
    wrench_editor::get_logger()->info(std::format(formatStr, ##__VA_ARGS__))
#define EDITOR_DEBUG(formatStr, ...)                                                               \
    wrench_editor::get_logger()->debug(std::format(formatStr, ##__VA_ARGS__))
#define EDITOR_TRACE(formatStr, ...)                                                               \
    wrench_editor::get_logger()->trace(std::format(formatStr, ##__VA_ARGS__))
