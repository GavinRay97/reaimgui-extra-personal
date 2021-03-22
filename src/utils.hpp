#ifndef REAIMGUI_EXTRA_UTILS_HPP
#define REAIMGUI_EXTRA_UTILS_HPP

#include <string>
#include <vector>

#include "reaper_imgui_functions.h"
#include <api_helper.hpp>
#include <imgui.h>

auto init_imgui(ImGui_Context* ctx) -> bool;
auto FRAME_GUARD(ImGui_Context* ctx) -> bool;
auto generate_reascript_apidef_string(const std::string& return_type,
                                      const std::vector<std::pair<std::string, std::string>>& args,
                                      const std::string& description) -> std::string;

void copyToBuffer(const std::string& value, char* buf, const size_t bufSize);
float getArrayValue(void* data, const int index);
std::vector<ImVec2> ImVec2_from_reaper_array(const reaper_array* points);
#endif