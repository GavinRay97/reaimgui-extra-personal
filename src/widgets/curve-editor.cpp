#include "./curve-editor.hpp"
#include "../utils.hpp"
#include "reaper_plugin_secrets.h"

// https://github.com/ocornut/imgui/issues/786#issuecomment-241206229
void CurveEditor(ImGui_Context* ctx, const char* label, double* size_w, double* size_h, reaper_array* points)
{
    if (!FRAME_GUARD(ctx))
    {
        return;
    };

    auto _points = make_ImVec2_from_reaper_array(points);
    if (ImGui::Curve(label, ImVec2(*size_w, *size_h), _points.size(), _points.data()))
    {
        // curve changed
    };
}

float CurveEditorValueAtPoint(ImGui_Context* ctx, double* point, const reaper_array* points)
{
    if (!FRAME_GUARD(ctx))
    {
        throw;
    };

    auto _points = make_ImVec2_from_reaper_array(points);
    return ImGui::CurveValue(*point, _points.size(), _points.data());
}

DEFINE_API(CurveEditor)
("void",
 {{"ImGui_Context*", "ctx"},
  {"const char*", "label"},
  {"double", "size_w"},
  {"double", "size_h"},
  {"reaper_array*", "points"}},
 "A curve editor. Pass it a size and width for the canvas/editor graph, the number of maximum points, and an array of "
 "points");

DEFINE_API(CurveEditorValueAtPoint)
("double", {{"ImGui_Context*", "ctx"}, {"double*", "point"}, {"const reaper_array*", "points"}},
 "Calculate the value at some position of the curve points. IE '0.7'");
