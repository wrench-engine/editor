#include "Config.h"

namespace wrench_editor
{
    static Config s_DefaultConfig
    {

    }

    const Config &getDefault()
    {
        return s_DefaultConfig;
    }

}
