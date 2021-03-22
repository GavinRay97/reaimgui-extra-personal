#include "./L2D-file-dialog.hpp"
#include "../utils.hpp"
#include "imgui.h"

// https://github.com/Limeoats/L2DFileDialog
// DOCS FROM GITHUB:
// Usage:
//
// Add L2DFileDialog.h to your C++ project and include it where you use ImGui. Then, set FileDialog::fileDialogOpen to
// true to set the open state. Finally, in your update method, check if FileDialog::fileDialogOpen == true and if so,
// call FileDialog::ShowFileDialog, passing in a char array as a buffer to store the chosen file/folder path.

DEFINE_API(
    void, Lime2DFileDialogue,
    (ImGui_Context*, ctx)(bool*, API_RW(fileDialogOpen))(char*, API_RWBIG(buf))(int, API_RWBIG_SZ(buf)),
    "A file dialogue. Requires a boolean for whether the dialogue should be open, and a string variable to store the, "
    "chosen file/folder path to.",
    {
        if (!FRAME_GUARD(ctx))
            throw;

        assertValid(API_RWBIG(buf));

        if (*API_RW(fileDialogOpen) == true)
        {
            std::string value{API_RWBIG(buf)};

            FileDialog::fileDialogOpen = true;
            FileDialog::ShowFileDialog(API_RW(fileDialogOpen), reinterpret_cast<char*>(&value), API_RWBIG_SZ(buf));
            copyToBuffer(value, API_RWBIG(buf), API_RWBIG_SZ(buf));
        }
    });
