#include "./toggle-button.hpp"
#include "../utils.hpp"

void ToggleButton(ImGui_Context* ctx, const char* name, bool* value)
{
    if (!FRAME_GUARD(ctx))
        throw;
    ImGui::ToggleButton(name, value);
}

DEFINE_API(ToggleButton)
("void", {{"ImGui_Context*", "ctx"}, {"const char*", "name"}, {"bool*", "value"}},
 "A toggle button, given an identifying name and a boolean value. It matches the current theme.");