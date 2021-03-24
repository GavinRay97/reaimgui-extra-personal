#include "../utils.hpp"

#include "./imnodes/imnodes.hpp"
#include "reaper_plugin_secrets.h"


////////////////////////////
// CONTEXT
///////////////////////////

DEFINE_API(imnodes::Context*, ImNodes_CreateContext, (ImGui_Context*, ctx), "Create imnodes context", {
    if (!FRAME_GUARD(ctx))
        throw;

    return imnodes::CreateContext();
});

DEFINE_API(void, ImNodes_DestroyContext, (ImGui_Context*, ctx)(imnodes::Context*, API_RO(imnodes_ctx)),
           "Destroy imnodes context. NULL = destroy current context", {
               if (!FRAME_GUARD(ctx))
                   throw;

               if (API_RO(imnodes_ctx))
               {
                   return imnodes::DestroyContext(API_RO(imnodes_ctx));
               }

               return imnodes::DestroyContext();
           });

DEFINE_API(imnodes::Context*, ImNodes_GetCurrentContext, (ImGui_Context*, ctx), "Get imnodes context", {
    if (!FRAME_GUARD(ctx))
        throw;

    return imnodes::CreateContext();
});

DEFINE_API(void, ImNodes_SetCurrentContext, (ImGui_Context*, ctx)(imnodes::Context*, imnodes_ctx),
           "Set imnodes context", {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::SetCurrentContext(imnodes_ctx);
           });

////////////////////////////
// STYLE
///////////////////////////

DEFINE_API(imnodes::Style*, ImNodes_GetStyle, (ImGui_Context*, ctx),
           "Returns the global style struct. See the struct declaration for default values.", {
               if (!FRAME_GUARD(ctx))
                   throw;

               return &imnodes::GetStyle();
           });

DEFINE_API(void, ImNodes_StyleColorsDark, (ImGui_Context*, ctx),
           "Style presets matching the dear imgui styles of the same name. (Dark = On by default)", {
               if (!FRAME_GUARD(ctx))
                   throw;

               imnodes::StyleColorsDark();
           });

DEFINE_API(void, ImNodes_StyleColorsClassic, (ImGui_Context*, ctx),
           "Style presets matching the dear imgui styles of the same name. (Dark = On by default)", {
               if (!FRAME_GUARD(ctx))
                   throw;

               imnodes::StyleColorsClassic();
           });

DEFINE_API(void, ImNodes_StyleColorsLight, (ImGui_Context*, ctx),
           "Style presets matching the dear imgui styles of the same name. (Dark = On by default)", {
               if (!FRAME_GUARD(ctx))
                   throw;

               imnodes::StyleColorsLight();
           });

DEFINE_API(void, ImNodes_PushColorStyle, (ImGui_Context*, ctx)(imnodes::ColorStyle, item)(int, color),
           "Use PushColorStyle and PopColorStyle to modify Style::colors mid-frame.", {
               if (!FRAME_GUARD(ctx))
                   throw;

               imnodes::PushColorStyle(item, color);
           });

DEFINE_API(void, ImNodes_PopColorStyle, (ImGui_Context*, ctx),
           "Use PushColorStyle and PopColorStyle to modify Style::colors mid-frame.", {
               if (!FRAME_GUARD(ctx))
                   throw;

               imnodes::PopColorStyle();
           });

DEFINE_API(void, ImNodes_PushStyleVar, (ImGui_Context*, ctx)(imnodes::StyleVar, style_item)(double, value),
           "Use PushStyleVar and PopStyleVar to modify Style::var mid-frame.", {
               if (!FRAME_GUARD(ctx))
                   throw;

               imnodes::PushStyleVar(style_item, value);
           });

DEFINE_API(void, ImNodes_PopStyleVar, (ImGui_Context*, ctx),
           "Use PushColorStyle and PopColorStyle to modify Style::var mid-frame.", {
               if (!FRAME_GUARD(ctx))
                   throw;

               imnodes::PopStyleVar();
           });

////////////////////////////
// NODE EDITOR
///////////////////////////

DEFINE_API(void, ImNodes_BeginNodeEditor, (ImGui_Context*, ctx),
           "The top-level function call. Call this before calling BeginNode/EndNode. Calling this function will result "
           "the node editor grid workspace being rendered.",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::BeginNodeEditor();
           });

DEFINE_API(void, ImNodes_EndNodeEditor, (ImGui_Context*, ctx), "", {
    if (!FRAME_GUARD(ctx))
        throw;

    return imnodes::EndNodeEditor();
});

////////////////////////////
// NODE
///////////////////////////

DEFINE_API(void, ImNodes_BeginNode, (ImGui_Context*, ctx)(int, id),
           "id can be any positive or negative integer, but INT_MIN is currently reserved for internal use.", {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::BeginNode(id);
           });

DEFINE_API(void, ImNodes_EndNode, (ImGui_Context*, ctx), "", {
    if (!FRAME_GUARD(ctx))
        throw;

    return imnodes::EndNode();
});

DEFINE_API(void, ImNodes_GetNodeDimensions, (ImGui_Context*, ctx)(int, id)(double*, API_W(x))(double*, API_W(y)),
           "Get 2D dimensions of a node", {
               if (!FRAME_GUARD(ctx))
                   return;

               ImVec2 dimensions = imnodes::GetNodeDimensions(id);

               if (API_W(x))
                   *API_W(x) = dimensions.x;

               if (API_W(y))
                   *API_W(y) = dimensions.y;
           });

DEFINE_API(void, ImNodes_BeginNodeTitleBar, (ImGui_Context*, ctx),
           "Place your node title bar content (such as the node title, using ImGui::Text) between the following "
           "function calls. These functions have to be called before adding any attributes, or the layout of the node "
           "will be incorrect.",
           {
               if (!FRAME_GUARD(ctx))
                   return;

               return imnodes::BeginNodeTitleBar();
           });

DEFINE_API(void, ImNodes_EndNodeTitleBar, (ImGui_Context*, ctx),
           "Place your node title bar content (such as the node title, using ImGui::Text) between the following "
           "function calls. These functions have to be called before adding any attributes, or the layout of the node "
           "will be incorrect.",
           {
               if (!FRAME_GUARD(ctx))
                   return;

               return imnodes::EndNodeTitleBar();
           });

DEFINE_API(void, ImNodes_BeginInputAttribute, (ImGui_Context*, ctx)(int, id)(imnodes::PinShape, pinshape),
           "Create an input attribute block. The pin is rendered on left side.\n Attributes are ImGui UI elements "
           "embedded within the node. Attributes can have pin shapes rendered next to "
           "them. Links are created between pins.\n The activity status of an attribute can be checked via the "
           "IsAttributeActive() and IsAnyAttributeActive() function calls. This is one easy way of checking for any "
           "changes made to an attribute's drag float UI, for instance.\n Each attribute id must be unique.",
           {
               if (!FRAME_GUARD(ctx))
                   return;

               if (!pinshape)
                   pinshape = imnodes::PinShape_CircleFilled;

               return imnodes::BeginInputAttribute(id, pinshape);
           });

DEFINE_API(void, ImNodes_EndInputAttribute, (ImGui_Context*, ctx), "", {
    if (!FRAME_GUARD(ctx))
        return;

    return imnodes::EndInputAttribute();
});

DEFINE_API(void, ImNodes_BeginOutputAttribute, (ImGui_Context*, ctx)(int, id)(imnodes::PinShape, pinshape),
           "Create an output attribute block. The pin is rendered on the right side.", {
               if (!FRAME_GUARD(ctx))
                   return;

               if (!pinshape)
                   pinshape = imnodes::PinShape_CircleFilled;

               return imnodes::BeginOutputAttribute(id, pinshape);
           });

DEFINE_API(void, ImNodes_EndOutputAttribute, (ImGui_Context*, ctx), "", {
    if (!FRAME_GUARD(ctx))
        return;

    return imnodes::EndOutputAttribute();
});

DEFINE_API(void, ImNodes_BeginStaticAttribute, (ImGui_Context*, ctx)(int, id),
           "Create a static attribute block. A static attribute has no pin, and therefore can't be linked to anything. "
           "However, you can still use IsAttributeActive() and IsAnyAttributeActive() to check for attribute activity.",
           {
               if (!FRAME_GUARD(ctx))
                   return;

               return imnodes::BeginStaticAttribute(id);
           });

DEFINE_API(void, ImNodes_EndStaticAttribute, (ImGui_Context*, ctx), "", {
    if (!FRAME_GUARD(ctx))
        return;

    return imnodes::EndStaticAttribute();
});

DEFINE_API(void, ImNodes_PushAttributeFlag, (ImGui_Context*, ctx)(imnodes::AttributeFlags, flag),
           "Push a single AttributeFlags value. By default, only AttributeFlags_None is set.", {
               if (!FRAME_GUARD(ctx))
                   return;

               return imnodes::PushAttributeFlag(flag);
           });

DEFINE_API(void, ImNodes_PopAttributeFlag, (ImGui_Context*, ctx), "Pop a single AttributeFlags value.", {
    if (!FRAME_GUARD(ctx))
        return;

    return imnodes::PopAttributeFlag();
});

DEFINE_API(void, ImNodes_Link, (ImGui_Context*, ctx)(int, id)(int, start_attribute_id)(int, end_attribute_id),
           "Render a link between attributes.\nThe attributes ids used here must match the ids used in "
           "Begin(Input|Output)Attribute function calls.\n The order of start_attr and end_attr doesn't make a "
           "difference for rendering the link.",
           {
               if (!FRAME_GUARD(ctx))
                   return;

               return imnodes::Link(id, start_attribute_id, end_attribute_id);
           });

DEFINE_API(void, ImNodes_SetNodeDraggable, (ImGui_Context*, ctx)(int, node_id)(const bool, draggable),
           "Enable or disable the ability to click and drag a specific node. \n The node's position can be expressed "
           "in three coordinate systems: \n * screen space coordinates, -- the origin is the upper left corner of the "
           "window.\n * editor space coordinates -- the origin is the upper left corner of the node editor window \n * "
           "grid space coordinates, -- the origin is the upper left corner of the node editor window, translated by "
           "the current editor panning vector (see EditorContextGetPanning() and EditorContextResetPanning())",
           {
               if (!FRAME_GUARD(ctx))
                   return;
               return imnodes::SetNodeDraggable(node_id, draggable);
           });

DEFINE_API(void, ImNodes_SetNodeScreenSpacePos,
           (ImGui_Context*, ctx)(int, node_id)(double, screen_space_pos_x)(double, screen_space_pos_y), "", {
               if (!FRAME_GUARD(ctx))
                   return;

               ImVec2 coords = ImVec2{static_cast<float>(screen_space_pos_x), static_cast<float>(screen_space_pos_y)};
               return imnodes::SetNodeScreenSpacePos(node_id, coords);
           });

DEFINE_API(void, ImNodes_SetNodeEditorSpacePos,
           (ImGui_Context*, ctx)(int, node_id)(double, editor_space_pos_x)(double, editor_space_pos_y), "", {
               if (!FRAME_GUARD(ctx))
                   return;

               ImVec2 coords = ImVec2{static_cast<float>(editor_space_pos_x), static_cast<float>(editor_space_pos_y)};
               return imnodes::SetNodeEditorSpacePos(node_id, coords);
           });

DEFINE_API(void, ImNodes_SetNodeGridSpacePos,
           (ImGui_Context*, ctx)(int, node_id)(double, grid_pos_x)(double, grid_pos_y), "", {
               if (!FRAME_GUARD(ctx))
                   return;

               ImVec2 coords = ImVec2{static_cast<float>(grid_pos_x), static_cast<float>(grid_pos_y)};
               return imnodes::SetNodeGridSpacePos(node_id, coords);
           });

DEFINE_API(void, ImNodes_GetNodeScreenSpacePos,
           (ImGui_Context*, ctx)(int, node_id)(double*, API_W(screen_space_pos_x))(double*, API_W(screen_space_pos_y)),
           "", {
               if (!FRAME_GUARD(ctx))
                   return;

               ImVec2 coords = imnodes::GetNodeScreenSpacePos(node_id);

               if (API_W(screen_space_pos_x))
                   *API_W(screen_space_pos_x) = coords.x;

               if (API_W(screen_space_pos_y))
                   *API_W(screen_space_pos_y) = coords.y;
           });

DEFINE_API(void, ImNodes_GetNodeEditorSpacePos,
           (ImGui_Context*, ctx)(int, node_id)(double*, API_W(editor_space_pos_x))(double*, API_W(editor_space_pos_y)),
           "", {
               if (!FRAME_GUARD(ctx))
                   return;

               ImVec2 coords = imnodes::GetNodeEditorSpacePos(node_id);

               if (API_W(editor_space_pos_x))
                   *API_W(editor_space_pos_x) = coords.x;

               if (API_W(editor_space_pos_y))
                   *API_W(editor_space_pos_y) = coords.y;
           });

DEFINE_API(void, ImNodes_GetNodeGridSpacePos,
           (ImGui_Context*, ctx)(int, node_id)(double*, API_W(grid_space_pos_x))(double*, API_W(grid_space_pos_y)), "",
           {
               if (!FRAME_GUARD(ctx))
                   return;

               ImVec2 coords = imnodes::GetNodeGridSpacePos(node_id);

               if (API_W(grid_space_pos_x))
                   *API_W(grid_space_pos_x) = coords.x;

               if (API_W(grid_space_pos_y))
                   *API_W(grid_space_pos_y) = coords.y;
           });

DEFINE_API(bool, ImNodes_IsEditorHovered, (ImGui_Context*, ctx),
           "Returns true if the current node editor canvas is being hovered over by the mouse, and is not blocked by "
           "any other windows.",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::IsEditorHovered();
           });

DEFINE_API(bool, ImNodes_IsNodeHovered, (ImGui_Context*, ctx)(int*, API_RW(node_id)),
           "The following functions return true if a UI element is being hovered over by the mouse cursor. Assigns the "
           "id of the UI element being hovered over to the function argument. Use these functions after "
           "EndNodeEditor() has been called. ",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::IsNodeHovered(API_RW(node_id));
           });

DEFINE_API(bool, ImNodes_IsLinkHovered, (ImGui_Context*, ctx)(int*, API_RW(link_id)),
           "The following functions return true if a UI element is being hovered over by the mouse cursor. Assigns the "
           "id of the UI element being hovered over to the function argument. Use these functions after "
           "EndNodeEditor() has been called. ",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::IsLinkHovered(API_RW(link_id));
           });

DEFINE_API(bool, ImNodes_IsPinHovered, (ImGui_Context*, ctx)(int*, API_RW(attribute_id)),
           "The following functions return true if a UI element is being hovered over by the mouse cursor. Assigns the "
           "id of the UI element being hovered over to the function argument. Use these functions after "
           "EndNodeEditor() has been called. ",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::IsPinHovered(API_RW(attribute_id));
           });

DEFINE_API(int, ImNodes_NumSelectedNodes, (ImGui_Context*, ctx),
           "Use The following two functions to query the number of selected nodes or links in the current editor. Use "
           "after calling EndNodeEditor().",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::NumSelectedNodes();
           });

DEFINE_API(int, ImNodes_NumSelectedLinks, (ImGui_Context*, ctx),
           "Use The following two functions to query the number of selected nodes or links in the current editor. Use "
           "after calling EndNodeEditor().",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::NumSelectedLinks();
           });

DEFINE_API(
    void, ImNodes_GetSelectedNodes, (ImGui_Context*, ctx)(reaper_array*, API_RW(node_ids)),
    "Get the selected node/link ids. The pointer argument should point to an integer array with at least as "
    "many elements as the respective NumSelectedNodes/NumSelectedLinks function call returned."
    "\n"
    "NOTE: Allocate a new REAPER array which has the size of the number of nodes. IE: "
    "reaper.new_array(reaper.ImGui_Extra_ImNodes_NumSelectedNodes()) so that the id's can be written out properly",
    {
        if (!FRAME_GUARD(ctx))
            return;

        // We allocate a temporary vector which can be used like an int array, to store the data we're going to write
        // back to REAPER
        std::vector<int> out_temp_array(API_RW(node_ids)->size, 0);

        // We pass a pointer to this int array to the imnodes function, and let it write out (mutate) the data in-place
        imnodes::GetSelectedNodes(out_temp_array.data());

        // Now iterate over the int vector and write the data directly to the reaper array pointer
        size_t i{0};
        for (const int node_id : out_temp_array)
        {
            API_RW(node_ids)->data[i++] = static_cast<double>(node_id);
        }
    });

DEFINE_API(
    void, ImNodes_GetSelectedLinks, (ImGui_Context*, ctx)(reaper_array*, link_ids),
    "Get the selected node/link ids. The pointer argument should point to an integer array with at least as "
    "many elements as the respective NumSelectedNodes/NumSelectedLinks function call returned."
    "\n"
    "NOTE: Allocate a new REAPER array which has the size of the number of nodes. IE: "
    "reaper.new_array(reaper.ImGui_Extra_ImNodes_NumSelectedLinks()) so that the id's can be written out properly",
    {
        if (!FRAME_GUARD(ctx))
            return;

        // We allocate a temporary vector which can be used like an int array, to store the data we're going to write
        // back to REAPER
        std::vector<int> out_temp_array(link_ids->size, 0);

        // We pass a pointer to this int array to the imnodes function, and let it write out (mutate) the data in-place
        imnodes::GetSelectedLinks(out_temp_array.data());

        // Now iterate over the int vector and write the data directly to the reaper array pointer
        size_t i{0};
        for (const int node_id : out_temp_array)
        {
            link_ids->data[i++] = static_cast<double>(node_id);
        }
    });

DEFINE_API(void, ImNodes_ClearNodeSelection, (ImGui_Context*, ctx),
           "Clears the list of selected nodes/links. Useful if you want to delete a selected node or link.", {
               if (!FRAME_GUARD(ctx))
                   return;
               return imnodes::ClearNodeSelection();
           });

DEFINE_API(void, ImNodes_ClearLinkSelection, (ImGui_Context*, ctx),
           "Clears the list of selected nodes/links. Useful if you want to delete a selected node or link.", {
               if (!FRAME_GUARD(ctx))
                   return;
               return imnodes::ClearLinkSelection();
           });

DEFINE_API(bool, ImNodes_IsAttributeActive, (ImGui_Context*, ctx),
           "Was the previous attribute active? This will continuously return true while the left mouse button is being "
           "pressed over the UI content of the attribute.",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::IsAttributeActive();
           });

DEFINE_API(bool, ImNodes_IsAnyAttributeActive, (ImGui_Context*, ctx)(int*, API_W(attribute_id)),
           "Was any attribute active? If so, sets the active attribute id to the output function argument.", {
               if (!FRAME_GUARD(ctx))
                   throw;

               return imnodes::IsAnyAttributeActive(API_W(attribute_id));
           });

DEFINE_API(bool, ImNodes_IsLinkStarted, (ImGui_Context*, ctx)(int*, API_W(started_at_attribute_id)),
           "Did the user start dragging a new link from a pin?", {
               if (!FRAME_GUARD(ctx))
                   throw;
               return imnodes::IsLinkStarted(API_W(started_at_attribute_id));
           });

DEFINE_API(bool, ImNodes_IsLinkDropped,
           (ImGui_Context*, ctx)(int*, API_W(started_at_attribute_id))(bool, API_RO(including_detached_links)),
           "Did the user drop the dragged link before attaching it to a pin?\n"
           "There are two different kinds of situations to consider when handling this event:\n"
           "1) a link which is created at a pin and then dropped\n"
           "2) an existing link which is detached from a pin and then dropped\n"
           "Use the including_detached_links flag to control whether this function triggers when the user detaches a "
           "link and drops it.",
           {
               if (!FRAME_GUARD(ctx))
                   throw;

               if (API_RO(including_detached_links))
               {
                   return imnodes::IsLinkDropped(API_W(started_at_attribute_id), API_RO(including_detached_links));
               }

               return imnodes::IsLinkDropped(API_W(started_at_attribute_id));
           });

// clang-format off
DEFINE_API(bool, ImNodes_IsLinkCreated,
           (ImGui_Context*,ctx)
           (int*, API_W(started_at_attribute_id))(int*, API_W(ended_at_attribute_id))
           (bool*, API_RWO(created_from_snap)),
           "Did the user finish creating a new link?", {
               if (!FRAME_GUARD(ctx))
                   throw;

               if (API_RWO(created_from_snap))
               {
                   return imnodes::IsLinkCreated(API_W(started_at_attribute_id), API_W(ended_at_attribute_id),
                                                 API_RWO(created_from_snap));
               }

               return imnodes::IsLinkCreated(API_W(started_at_attribute_id), API_W(ended_at_attribute_id));
           });

DEFINE_API(bool, ImNodes_IsLinkCreated2,
           (ImGui_Context*,ctx)
           (int*, API_W(started_at_node_id))(int*, API_W(started_at_attribute_id))
           (int*, API_W(ended_at_node_id))(int*, API_W(ended_at_attribute_id))
           (bool*, API_RWO(created_from_snap)),
           "Did the user finish creating a new link?", {
               if (!FRAME_GUARD(ctx))
                   throw;

               if (API_RWO(created_from_snap))
               {
                   return imnodes::IsLinkCreated(API_W(started_at_node_id), API_W(started_at_attribute_id),
                                                  API_W(ended_at_node_id),  API_W(ended_at_attribute_id), API_RWO(created_from_snap));
               }

                   return imnodes::IsLinkCreated(API_W(started_at_node_id), API_W(started_at_attribute_id),
                                                  API_W(ended_at_node_id),  API_W(ended_at_attribute_id));
           });
// clang-format on

DEFINE_API(bool, ImNodes_IsLinkDestroyed, (ImGui_Context*, ctx)(int*, API_W(link_id)),
           "Was an existing link detached from a pin by the user? The detached link's id is assigned to the output "
           "argument link_id.",
           {
               if (!FRAME_GUARD(ctx))
                   throw;
               return imnodes::IsLinkDestroyed(API_W(link_id));
           });

// Use the following functions to write the editor context's state to a string, or directly to a
// file. The editor context is serialized in the INI file format.

// const char* SaveCurrentEditorStateToIniString(size_t* data_size = NULL);
// const char* SaveEditorStateToIniString(const EditorContext* editor, size_t* data_size = NULL);

// void LoadCurrentEditorStateFromIniString(const char* data, size_t data_size);
// void LoadEditorStateFromIniString(EditorContext* editor, const char* data, size_t data_size);

// void SaveCurrentEditorStateToIniFile(const char* file_name);
// void SaveEditorStateToIniFile(const EditorContext* editor, const char* file_name);

// void LoadCurrentEditorStateFromIniFile(const char* file_name);
// void LoadEditorStateFromIniFile(EditorContext* editor, const char* file_name);