#include <cassert>
#include <wrench_editor/logging/logging.h>

namespace wrench_editor {
WrenchEditorLogger::WrenchEditorLogger()
    : logx::Logger() {
}

const char *WrenchEditorLogger::getLevelName_Unsafe(logx::Level level) const {
    static const std::unordered_map<logx::Level, const char *> levelNames{
        {logx::Level::critical, "EDITOR::CRITICAL"},
        {logx::Level::error, "EDITOR::ERROR"},
        {logx::Level::warning, "EDITOR::WARNING"},
        {logx::Level::info, "EDITOR::INFO"},
        {logx::Level::debug, "EDITOR::DEBUG"},
        {logx::Level::trace, "EDITOR::TRACE"},
    };

    auto it = levelNames.find(level);
    if (it != levelNames.end()) {
        return it->second;
    }

    return nullptr;
}

static std::unique_ptr<logx::Logger> s_logger{nullptr};

logx::Logger *get_logger() {
    if (!s_logger) {
        s_logger = std::make_unique<logx::Logger>();
    }
    return s_logger.get();
}

} // namespace wrench_editor