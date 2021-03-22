#include "../utils.hpp"
#include "./toggle-button.hpp"

DEFINE_API(void, ToggleButton, (ImGui_Context*, ctx)(const char*, name)(bool*, API_RW(value)),
           "A toggle button, given an identifying name and a boolean value. It matches the current theme.", {
               if (!FRAME_GUARD(ctx))
                    throw;
               ImGui::ToggleButton(name, API_RW(value));
           });