#include "./curve-editor-lumix.hpp"
#include "../utils.hpp"

// https://github.com/ocornut/imgui/issues/786#issuecomment-358106252
void CurveEditorLumix(ImGui_Context* ctx, const char* label, reaper_array* values, double* size_w, double* size_h,
                      const int flags, int* new_count)
{
    if (!FRAME_GUARD(ctx))
    {
        return;
    };

    auto points = make_ImVec2_from_reaper_array(values);

    int _flags = (int)ImGui::CurveEditorFlags::NO_TANGENTS | (int)ImGui::CurveEditorFlags::SHOW_GRID;

    if (ImGui::CurveEditor(label, (float*)points.data(), points.size(), ImVec2(*size_w, *size_h), _flags, new_count))
    {
    };
}

DEFINE_API(CurveEditorLumix)
("void",
 {{"ImGui_Context*", "ctx"},
  {"const char*", "label"},
  {"reaper_array*", "values"},
  {"double*", "size_w"},
  {"double*", "size_h"},
  {"double", "flags"},
  {"double*", "new_count"}},
 "A curve editor.");
