#include "../utils.hpp"
#include "./bezier.hpp"
#include <reaper_plugin_secrets.h>

// https://github.com/ocornut/imgui/issues/786#issuecomment-479539045
DEFINE_API(void, Bezier, (ImGui_Context*, ctx)(const char*, name)(reaper_array*, points), "A Bezier curve editor", {
    if (!FRAME_GUARD(ctx))
    {
        throw;
    }

    if (ImGui::Bezier(name, reinterpret_cast<float*>(points->data)))
    {
        // stuff
    }
});
