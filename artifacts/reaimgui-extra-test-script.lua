local ctx = reaper.ImGui_CreateContext("My script", 620, 500)

local theme_map = {
    "DefaultClassic", "DefaultDark", "DefaultLight", "Gray", "Light",
    "BlackCodz01", "DarkCodz01", "GrayCodz01", "Purple", "Cherry", "DarkOpaque",
    "Soft", "EdinBlack", "EdinWhite", "Maya", "LightGreen", "Design", "Dracula",
    "Greenish", "C64", "PhotoStore", "CorporateGreyFlat", "CorporateGreyFramed",
    "VisualDark", "SteamingLife", "SoftLife", "GoldenBlack", "Windowed",
    "OverShiftedBlack", "AieKickGreenBlue", "AieKickRedDark",
    "DarkOpaqueInverse", "GrayCodz01Inverse", "PurpleInverse",
    "LightGreenInverse", "DesignInverse"
}

local theme_map_combo_box_string = ""
for _, val in ipairs(theme_map) do
    theme_map_combo_box_string = theme_map_combo_box_string .. val .. "\31"
end

local theme = 9 -- "CHERRY"

local SEPARATOR = function()
    reaper.ImGui_Spacing(ctx)
    reaper.ImGui_Spacing(ctx)
    reaper.ImGui_Spacing(ctx)
    reaper.ImGui_Separator(ctx)
end

local function make_random_xy_points_reaper_array(num_points, max_num)
    local numbers = {}

    for x = 1, num_points * 2 do
        local random_num
        if max_num then
            table.insert(numbers, x)
            random_num = math.random(max_num)
        else
            -- Float between 0..1
            table.insert(numbers, x / 10)
            random_num = math.random()
        end
        table.insert(numbers, random_num)
    end

    return reaper.new_array(numbers, num_points * 2)
end

local bezier_array = reaper.new_array({0.0, 0.0}, 2)
local lumix_curve_editor_points = make_random_xy_points_reaper_array(5, 100)
local other_curve_editor_points = make_random_xy_points_reaper_array(5)

local out_ptr_curve_editor_new_count = 0
local my_toggle_bool = false

local curve_editor_size_w, curve_editor_size_h = 300, 150

local markdown_string = [[
# Header 1
The following should be an unordered list:
- One
- Two
- Three
  - Testing for sub-list ability
  - Another sub-list item

The following should be bulleted list:
  *  One
  *  Two
  *  Three
    *  Testing for sub-list ability
    *  Another sub-list item
    
===================================================
]]

function loop()
    local rv

    if reaper.ImGui_IsCloseRequested(ctx) then
        reaper.ImGui_DestroyContext(ctx)
        return
    end

    reaper.ImGui_SetNextWindowPos(ctx, 0, 0)
    reaper.ImGui_SetNextWindowSize(ctx, reaper.ImGui_GetDisplaySize(ctx))
    reaper.ImGui_Begin(ctx, "wnd", nil, reaper.ImGui_WindowFlags_NoDecoration())

    reaper.ImGui_Extra_LoadPresetStyle(ctx, theme)

    local version = reaper.ImGui_GetVersion()
    reaper.ImGui_Text(ctx, "ImGui v" .. version)

    my_toggle_bool = reaper.ImGui_Extra_ToggleButton(ctx, "My Toggle",
                                                     my_toggle_bool)
    reaper.ImGui_Text(ctx, string.format("%s", my_toggle_bool))

    _, theme = reaper.ImGui_Combo(ctx, "ImGui Preset Style", theme,
                                  theme_map_combo_box_string)

    reaper.ImGui_Extra_Markdown(ctx, markdown_string)

    reaper.ImGui_Text(ctx, "reaper.array points:")
    for idx, val in ipairs(bezier_array.table()) do
        reaper.ImGui_Text(ctx, val)
    end
    reaper.ImGui_Extra_Bezier(ctx, "Bezier", bezier_array)

    SEPARATOR()

    reaper.ImGui_Text(ctx, "reaper.array points:")
    for idx, val in ipairs(lumix_curve_editor_points.table()) do
        reaper.ImGui_Text(ctx, val)
    end
    reaper.ImGui_Text(ctx, out_ptr_curve_editor_new_count)

    reaper.ImGui_Extra_CurveEditorLumix(ctx, "Curve editor",
                                        lumix_curve_editor_points,
                                        curve_editor_size_w,
                                        curve_editor_size_h, 1,
                                        out_ptr_curve_editor_new_count)

    SEPARATOR()

    reaper.ImGui_Text(ctx, "reaper.array points:")
    for idx, val in ipairs(other_curve_editor_points.table()) do
        reaper.ImGui_Text(ctx, val)
    end

    reaper.ImGui_Extra_CurveEditor(ctx, "Other curve editor",
                                   curve_editor_size_w, curve_editor_size_h,
                                   other_curve_editor_points)

    reaper.ImGui_End(ctx)
    reaper.defer(loop)
end

reaper.defer(loop)
