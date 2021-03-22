#include "./markdown.hpp"
#include "../utils.hpp"

#include <imgui.h>
// Following includes for Windows LinkCallback
#define WIN32_LEAN_AND_MEAN
#include "Shellapi.h"
#include <Windows.h>
#include <string>

const auto STD_FONT_PATH = "./resources/Roboto-Regular.ttf";
const auto BOLD_FONT_PATH = "./resources/Roboto-Bold.ttf";

// void LinkCallback(ImGui::MarkdownLinkCallbackData data_);
inline ImGui::MarkdownImageData ImageCallback(ImGui::MarkdownLinkCallbackData data_);
static ImFont* H1 = NULL;
static ImFont* H2 = NULL;
static ImFont* H3 = NULL;
static ImGui::MarkdownConfig mdConfig;
// void LinkCallback(ImGui::MarkdownLinkCallbackData data_)
// {
//     std::string url(data_.link, data_.linkLength);
//     if (!data_.isImage)
//     {
//         ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
//     }
// }
inline ImGui::MarkdownImageData ImageCallback(ImGui::MarkdownLinkCallbackData data_)
{
    // In your application you would load an image based on data_ input. Here we just use the imgui font texture.
    ImTextureID image = ImGui::GetIO().Fonts->TexID;
    // > C++14 can use ImGui::MarkdownImageData imageData{ true, false, image, ImVec2( 40.0f, 20.0f ) };
    ImGui::MarkdownImageData imageData;
    imageData.isValid = true;
    imageData.useLinkCallback = false;
    imageData.user_texture_id = image;
    imageData.size = ImVec2(40.0f, 20.0f);

    // For image resize when available size.x > image width, add
    ImVec2 const contentSize = ImGui::GetContentRegionAvail();
    if (imageData.size.x > contentSize.x)
    {
        float const ratio = imageData.size.y / imageData.size.x;
        imageData.size.x = contentSize.x;
        imageData.size.y = contentSize.x * ratio;
    }
    return imageData;
}

void LoadFonts(float fontSize_ = 12.0f)
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    // Base font
    io.Fonts->AddFontFromFileTTF(STD_FONT_PATH, fontSize_);
    // Bold headings H2 and H3
    H2 = io.Fonts->AddFontFromFileTTF(BOLD_FONT_PATH, fontSize_);
    H3 = mdConfig.headingFormats[1].font;
    // bold heading H1
    float fontSizeH1 = fontSize_ * 1.1f;
    H1 = io.Fonts->AddFontFromFileTTF(BOLD_FONT_PATH, fontSizeH1);
}

void ExampleMarkdownFormatCallback(const ImGui::MarkdownFormatInfo& markdownFormatInfo_, bool start_)
{
    // Call the default first so any settings can be overwritten by our implementation.
    // Alternatively could be called or not called in a switch statement on a case by case basis.
    // See defaultMarkdownFormatCallback definition for furhter examples of how to use it.
    ImGui::defaultMarkdownFormatCallback(markdownFormatInfo_, start_);

    switch (markdownFormatInfo_.type)
    {
    // example: change the colour of heading level 2
    case ImGui::MarkdownFormatType::HEADING: {
        if (markdownFormatInfo_.level == 2)
        {
            if (start_)
            {
                // ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
            }
            else
            {
                // ImGui::PopStyleColor();
            }
        }
        break;
    }
    default: {
        break;
    }
    }
}
void MarkdownHandler(const std::string& markdown_)
{
    // You can make your own Markdown function with your prefered string container and markdown config.
    // > C++14 can use ImGui::MarkdownConfig mdConfig{ LinkCallback, NULL, ImageCallback, ICON_FA_LINK, { { H1, true },
    // { H2, true }, { H3, false } }, NULL };
    mdConfig.linkCallback = nullptr;
    mdConfig.tooltipCallback = nullptr;
    mdConfig.imageCallback = ImageCallback;
    mdConfig.linkIcon = nullptr;
    mdConfig.headingFormats[0] = {H1, true};
    mdConfig.headingFormats[1] = {H2, true};
    mdConfig.headingFormats[2] = {H3, false};
    mdConfig.userData = nullptr;
    mdConfig.formatCallback = ExampleMarkdownFormatCallback;
    ImGui::Markdown(markdown_.c_str(), markdown_.length(), mdConfig);
}

DEFINE_API(void, Markdown, (ImGui_Context*, ctx)(const char*, text), "Render Markdown to ImGui Elements", {
    if (!FRAME_GUARD(ctx))
        throw;

    MarkdownHandler(text);
});
