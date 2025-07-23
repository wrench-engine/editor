#include "Config.h"
#include "WrenchEditor.h"

using namespace wrench_editor;

int main() {
    Config config;
    WrenchEditor editor(config);
    return editor.run();
}
