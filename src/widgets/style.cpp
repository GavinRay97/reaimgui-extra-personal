#include "../utils.hpp"
#include "./color-themes/style-serializer.hpp"

DEFINE_API(bool, LoadPresetStyle, (ImGui_Context*, ctx)(int, style),
           "Load an ImGui style from a pallete of presets: "
           "DefaultClassic = 0"
           "DefaultDark"
           "DefaultGray"
           "Light"
           "BlackCodz01"
           "DarkCodz01"
           "GrayCodz01"
           "Purple"
           "Cherry"
           "DarkOpaque"
           "Soft"
           "EdinBlack"
           "EdinWhite"
           "Maya"
           "LightGreen"
           "Design"
           "Dracula"
           "Greenish"
           "C64"
           "PhotoStore"
           "CorporateGreyFlat"
           "CorporateGreyFramed"
           "VisualDark"
           "SteamingLife"
           "SoftLife"
           "GoldenBlack"
           "Windowed"
           "OverShiftedBlack"
           "AieKickGreenBlue"
           "AieKickRedDark"
           "DarkOpaqueInverse"
           "GrayCodz01Inverse"
           "PurpleInverse"
           "LightGreenInverse"
           "DesignInverse",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return ImGui::ResetStyle(style, ImGui::GetStyle());
           });