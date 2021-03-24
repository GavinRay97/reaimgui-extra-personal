#include <string>
#include <vector>

#include "api.hpp"
#include "api_vararg.hpp"

#include "reaper_imgui_functions.h"
#include "reaper_plugin_secrets.h"
#include <api_helper.hpp>
#include <imgui.h>

#include "./utils.hpp"

// Grab handles to internal ReaImGui functions
ReaImGuiFunc<bool(const char* version, size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_vert,
                  size_t sz_idx, char** p_error)>
    ImGui_CheckVersionAndDataLayout{"ImGui_CheckVersionAndDataLayout"};

ReaImGuiFunc<void(ImGuiMemAllocFunc* p_alloc_func, ImGuiMemFreeFunc* p_free_func, void** p_user_data)>
    ImGui_GetAllocatorFunctions{"ImGui_GetAllocatorFunctions"};

ReaImGuiFunc<ImGuiContext*(ImGui_Context* ctx, bool enterFrame)> ImGui_GetInternalContext{"ImGui_GetInternalContext"};

// Handles setting allocators and checking memory layouts + versions
auto init_imgui(ImGui_Context* ctx) -> bool
{
    static bool init;
    if (init)
    {
        return true;
    }

    // This fails if the ImGui versions or memory layouts of structures differs between the .dll's (dynamic libs)
    char* error;
    if (!ImGui_CheckVersionAndDataLayout(IMGUI_VERSION, sizeof(ImGuiIO), sizeof(ImGuiStyle), sizeof(ImVec2),
                                         sizeof(ImVec4), sizeof(ImDrawVert), sizeof(ImDrawIdx), &error))
    {
        return false;
    }

    // Initialize empty placeholders for allocator and userdata to be set below
    void* userData;
    ImGuiMemAllocFunc allocFunc;
    ImGuiMemFreeFunc freeFunc;

    ImGui_GetAllocatorFunctions(&allocFunc, &freeFunc, &userData);
    ImGui::SetAllocatorFunctions(allocFunc, freeFunc, userData);

    return init = true;
}

auto FRAME_GUARD(ImGui_Context* ctx) -> bool
{
    if (!init_imgui(ctx))
    {
        return false; // TODO: handle error (mismatched imgui)
    }

    ImGuiContext* imgui{ImGui_GetInternalContext(ctx, true)};

    if (imgui == nullptr)
    {
        return false; // TODO: handle error (ctx is likely invalid)
    }

    ImGui::SetCurrentContext(imgui);
    return true;
}

auto generate_reascript_apidef_string(const std::string& return_type,
                                      const std::vector<std::pair<std::string, std::string>>& args,
                                      const std::string& description) -> std::string
{
    using namespace std::string_literals;

    std::string ReaScriptAPIDef;
    std::string null_terminator = "\0"s;

    // Make required ReaScript definition string, of format:
    // "void\0ImGui_Context*\0ctx\0Lorem ipsum dolor sit amet"
    // "<return type>\0<comma-separated arg types>\0<comma-separated arg names>\0<description>"

    // <return type>\0
    ReaScriptAPIDef.append(return_type + null_terminator);

    // <comma-separated arg types>\0
    auto first_arg_type_added = false;
    for (const auto& [key, _] : args)
    {
        if (first_arg_type_added)
        {
            ReaScriptAPIDef.append(",");
        }
        else
        {
            first_arg_type_added = true;
        }
        ReaScriptAPIDef.append(key);
    }
    ReaScriptAPIDef.append(null_terminator);

    // <comma-separated arg names>\0
    auto first_arg_value_added = false;
    for (const auto& [_, value] : args)
    {
        if (first_arg_value_added)
        {
            ReaScriptAPIDef.append(",");
        }
        else
        {
            first_arg_value_added = true;
        }
        ReaScriptAPIDef.append(value);
    }
    ReaScriptAPIDef.append(null_terminator);

    // <description>
    ReaScriptAPIDef.append(description);
    return ReaScriptAPIDef;
}

// https://github.com/cfillion/reaimgui/blob/7a05b4d2c44a4a9f4c51789a40acb51dd58a109a/src/api_input.cpp#L25
void copyToBuffer(const std::string& value, char* buf, const size_t bufSize)
{
    int newSize{};
    if (value.size() >= bufSize && realloc_cmd_ptr(&buf, &newSize, value.size()))
    {
        // the buffer is no longer null-terminated after using realloc_cmd_ptr!
        std::memcpy(buf, value.c_str(), newSize);
    }
    else
    {
        const size_t limit{(((bufSize - 1) < (value.size())) ? (bufSize - 1) : (value.size()))};
        std::memcpy(buf, value.c_str(), limit);
        buf[limit] = '\0';
    }
}

// https://github.com/cfillion/reaimgui/blob/7a05b4d2c44a4a9f4c51789a40acb51dd58a109a/src/api_plots.cpp#L22-L26
static float getArrayValue(void* data, const int index)
{
    const double value{static_cast<double*>(data)[index]};
    return static_cast<float>(value);
}

// https://github.com/cfillion/reaimgui/blob/62b77d3e9e6b092c1f7311d7c2692122a4c3931a/src/api_drawlist.cpp#L218
std::vector<ImVec2> ImVec2_from_reaper_array(const reaper_array* points)
{
    assertValid(points);

    if (points->size % 2)
        throw reascript_error{"an odd amount of points was provided (expected x,y pairs)"};

    std::vector<ImVec2> out;
    out.reserve(points->size / 2);
    for (unsigned int i = 0; i < points->size - 1; i += 2)
        out.push_back(ImVec2(points->data[i], points->data[i + 1]));
    return out;
}

reaper_array reaper_array_from_ImVec2(reaper_array* array, std::vector<ImVec2> points)
{
    assertValid(array);

    if (array->size % 2)
        throw reascript_error{"an odd amount of points was provided (expected x,y pairs)"};

    size_t i{0};
    for (const ImVec2& point : points)
    {
        array->data[i++] = point.x;
        array->data[i++] = point.y;
    }
}
