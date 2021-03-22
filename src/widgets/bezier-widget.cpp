#include "../utils.hpp"
#include "./bezier.hpp"
#include "reaper_plugin_secrets.h"

// https://github.com/ocornut/imgui/issues/786#issuecomment-479539045
void Bezier(ImGui_Context* ctx, const char* name, reaper_array* points)
{

    if (!FRAME_GUARD(ctx))
    {
        throw;
    }

    if (ImGui::Bezier("test", reinterpret_cast<float*>(points->data)))
    {
        // stuff
    }
};

DEFINE_API(Bezier)
("void", {{"ImGui_Context*", "ctx"}, {"const char*", "name"}, {"reaper_array*", "points"}}, "A Bezier curve editor");
