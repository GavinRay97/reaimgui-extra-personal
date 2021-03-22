#include <string>
#include <vector>

#include "reaper_imgui_functions.h"

#include "api.hpp"
#include "api_vararg.hpp"

#include "reaimgui_errors.hpp"
#include "reaper_plugin_secrets.h"
#include <imgui.h>

auto init_imgui(ImGui_Context* ctx) -> bool;
auto FRAME_GUARD(ImGui_Context* ctx) -> bool;
auto generate_reascript_apidef_string(const std::string& return_type,
                                      const std::vector<std::pair<std::string, std::string>>& args,
                                      const std::string& description) -> std::string;

template <auto F> struct APIBuilder
{
    const char* name;

    auto create(const std::string& type, const std::vector<std::pair<std::string, std::string>>& args,
                const std::string& help)
    {
        static const std::string& definition{generate_reascript_apidef_string(type, args, help)};
        return API{name, reinterpret_cast<void*>(F), reinterpret_cast<void*>(&InvokeReaScriptAPI<F>),
                   definition.c_str()};
    }
};

template <typename T> inline void assertValid(T* ptr)
{
    if (ptr)
        return;

    std::string type;
    if constexpr (std::is_class_v<T>)
        type = T::api_type_name;

    char message[255];
    snprintf(message, sizeof(message), "expected valid %s*, got %p", type.c_str(), ptr);
    throw reascript_error{message};
}

static std::vector<ImVec2> make_ImVec2_from_reaper_array(const reaper_array* points)
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

#define DEFINE_API(name) static const API API##name = APIBuilder<name>{#name}.create
