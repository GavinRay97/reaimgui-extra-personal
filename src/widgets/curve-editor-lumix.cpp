#include "./curve-editor-lumix.hpp"
#include "../utils.hpp"

// https://github.com/ocornut/imgui/issues/786#issuecomment-358106252

// clang-format off
DEFINE_API(void, CurveEditorLumix,
           (ImGui_Context*, ctx)(const char*, label)(reaper_array*, values)(double*, size_w)
           (double*, size_h)(int, flags)(int*, new_count), "A curve editor.", {
               if (!FRAME_GUARD(ctx))
                   return;

               auto points = ImVec2_from_reaper_array(values);

               // I'm hardcoding this for now
               int _flags = (int)ImGui::CurveEditorFlags::NO_TANGENTS | (int)ImGui::CurveEditorFlags::SHOW_GRID;

               if (ImGui::CurveEditor(label, (float*)points.data(), points.size(), ImVec2(*size_w, *size_h), _flags,
                                      new_count))
               {
               };
           });
// clang-format on