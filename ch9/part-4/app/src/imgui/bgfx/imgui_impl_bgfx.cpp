// Derived from this Gist by Richard Gale:
//     https://gist.github.com/RichardGale/6e2b74bc42b3005e08397236e4be0fd0

// ImGui bgfx binding
// In this binding, ImTextureID is used to store an OpenGL 'GLuint' texture
// identifier. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See
// main.cpp for an example of using this. If you use this binding you'll need to
// call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(),
// ImGui::Render() and ImGui_ImplXXXX_Shutdown(). If you are new to ImGui, see
// examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#include "imgui_impl_bgfx.h"
#include <imgui.h>

// bgfx/bx
#include <bgfx/c99/bgfx.h>
#include <bx/math.h>
#include <stdio.h>

// Data
static uint8_t g_View = 255;
static bgfx_texture_handle_t g_FontTexture = BGFX_INVALID_HANDLE;
static bgfx_program_handle_t g_ShaderHandle = BGFX_INVALID_HANDLE;
static bgfx_uniform_handle_t g_AttribLocationTex = BGFX_INVALID_HANDLE;
static bgfx_vertex_layout_t g_VertexLayout;

// This is the main rendering function that you have to implement and call after
// ImGui::Render(). Pass ImGui::GetDrawData() to this function.
// Note: If text or lines are blurry when integrating ImGui into your engine,
// in your Render function, try translating your projection matrix by
// (0.5f,0.5f) or (0.375f,0.375f)
void ImGui_Implbgfx_RenderDrawLists(ImDrawData* draw_data) {
  // Avoid rendering when minimized, scale coordinates for retina displays
  // (screen coordinates != framebuffer coordinates)
  ImGuiIO& io = ImGui::GetIO();
  int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
  int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
  if (fb_width == 0 || fb_height == 0) {
    return;
  }

  draw_data->ScaleClipRects(io.DisplayFramebufferScale);

  // Setup render state: alpha-blending enabled, no face culling,
  // no depth testing, scissor enabled
  uint64_t state =
    BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA
    | BGFX_STATE_BLEND_FUNC(
      BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);

  const bgfx_caps_t* caps = bgfx_get_caps();

  // Setup viewport, orthographic projection matrix
  float ortho[16];
  bx::mtxOrtho(
    ortho, 0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, 0.0f, 1000.0f, 0.0f,
    caps->homogeneousDepth);
  bgfx_set_view_transform(g_View, NULL, ortho);
  bgfx_set_view_rect(g_View, 0, 0, (uint16_t)fb_width, (uint16_t)fb_height);

  // Render command lists
  for (int n = 0; n < draw_data->CmdListsCount; n++) {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];

    bgfx_transient_vertex_buffer_t tvb;
    bgfx_transient_index_buffer_t tib;

    uint32_t numVertices = (uint32_t)cmd_list->VtxBuffer.size();
    uint32_t numIndices = (uint32_t)cmd_list->IdxBuffer.size();

    if (
      (numVertices
       != bgfx_get_avail_transient_vertex_buffer(numVertices, &g_VertexLayout))
      || (numIndices != bgfx_get_avail_transient_index_buffer(numIndices, false))) {
      // not enough space in transient buffer, quit drawing the rest...
      break;
    }

    bgfx_alloc_transient_vertex_buffer(&tvb, numVertices, &g_VertexLayout);
    bgfx_alloc_transient_index_buffer(&tib, numIndices, false);

    ImDrawVert* verts = (ImDrawVert*)tvb.data;
    memcpy(
      verts, cmd_list->VtxBuffer.begin(), numVertices * sizeof(ImDrawVert));

    ImDrawIdx* indices = (ImDrawIdx*)tib.data;
    memcpy(
      indices, cmd_list->IdxBuffer.begin(), numIndices * sizeof(ImDrawIdx));

    for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
      const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

      if (pcmd->UserCallback) {
        pcmd->UserCallback(cmd_list, pcmd);
      } else {
        const uint16_t xx = (uint16_t)bx::max(pcmd->ClipRect.x, 0.0f);
        const uint16_t yy = (uint16_t)bx::max(pcmd->ClipRect.y, 0.0f);
        bgfx_set_scissor(
          xx, yy, (uint16_t)bx::min(pcmd->ClipRect.z, 65535.0f) - xx,
          (uint16_t)bx::min(pcmd->ClipRect.w, 65535.0f) - yy);

        bgfx_set_state(state, 0);
        bgfx_texture_handle_t texture = {
          (uint16_t)((intptr_t)pcmd->TextureId & 0xffff)};
        bgfx_set_texture(0, g_AttribLocationTex, texture, UINT32_MAX);
        bgfx_set_transient_vertex_buffer(0, &tvb, 0, numVertices);
        bgfx_set_transient_index_buffer(&tib, pcmd->IdxOffset, pcmd->ElemCount);
        bgfx_submit(g_View, g_ShaderHandle, 0, BGFX_DISCARD_ALL);
      }
    }
  }
}

bool ImGui_Implbgfx_CreateFontsTexture() {
  // Build texture atlas
  ImGuiIO& io = ImGui::GetIO();
  unsigned char* pixels;
  int width, height;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

  // Upload texture to graphics system
  g_FontTexture = bgfx_create_texture_2d(
    (uint16_t)width, (uint16_t)height, false, 1, BGFX_TEXTURE_FORMAT_BGRA8, 0,
    bgfx_copy(pixels, width * height * 4));

  // Store our identifier
  io.Fonts->TexID = (void*)(intptr_t)g_FontTexture.idx;

  return true;
}

#include "fs_ocornut_imgui.bin.h"
#include "vs_ocornut_imgui.bin.h"

bool ImGui_Implbgfx_CreateDeviceObjects() {
  bgfx_renderer_type renderer_type = bgfx_get_renderer_type();

  const bgfx_memory_t* vs_mem = nullptr;
  const bgfx_memory_t* fs_mem = nullptr;

  switch (renderer_type) {
    case BGFX_RENDERER_TYPE_DIRECT3D11:
      vs_mem =
        bgfx_make_ref(vs_ocornut_imgui_dx11, sizeof(vs_ocornut_imgui_dx11));
      fs_mem =
        bgfx_make_ref(fs_ocornut_imgui_dx11, sizeof(fs_ocornut_imgui_dx11));
      break;
    case BGFX_RENDERER_TYPE_OPENGL:
      vs_mem =
        bgfx_make_ref(vs_ocornut_imgui_glsl, sizeof(vs_ocornut_imgui_glsl));
      fs_mem =
        bgfx_make_ref(fs_ocornut_imgui_glsl, sizeof(fs_ocornut_imgui_glsl));
      break;
    case BGFX_RENDERER_TYPE_METAL:
      vs_mem =
        bgfx_make_ref(vs_ocornut_imgui_mtl, sizeof(vs_ocornut_imgui_mtl));
      fs_mem =
        bgfx_make_ref(fs_ocornut_imgui_mtl, sizeof(fs_ocornut_imgui_mtl));
      break;
    default:
      fprintf(stderr, "Unsupported renderer");
      exit(0);
      break;
  }

  bgfx_shader_handle_t vsh = bgfx_create_shader(vs_mem);
  bgfx_shader_handle_t fsh = bgfx_create_shader(fs_mem);
  g_ShaderHandle = bgfx_create_program(vsh, fsh, true);

  bgfx_vertex_layout_begin(&g_VertexLayout, renderer_type);
  bgfx_vertex_layout_add(
    &g_VertexLayout, BGFX_ATTRIB_POSITION, 2, BGFX_ATTRIB_TYPE_FLOAT, false,
    false);
  bgfx_vertex_layout_add(
    &g_VertexLayout, BGFX_ATTRIB_TEXCOORD0, 2, BGFX_ATTRIB_TYPE_FLOAT, true,
    false);
  bgfx_vertex_layout_add(
    &g_VertexLayout, BGFX_ATTRIB_COLOR0, 4, BGFX_ATTRIB_TYPE_UINT8, true,
    false);
  bgfx_vertex_layout_end(&g_VertexLayout);

  g_AttribLocationTex =
    bgfx_create_uniform("g_AttribLocationTex", BGFX_UNIFORM_TYPE_SAMPLER, 1);

  ImGui_Implbgfx_CreateFontsTexture();

  return true;
}

void ImGui_Implbgfx_InvalidateDeviceObjects() {
  bgfx_destroy_uniform(g_AttribLocationTex);
  bgfx_destroy_program(g_ShaderHandle);

  if (BGFX_HANDLE_IS_VALID(g_FontTexture)) {
    bgfx_destroy_texture(g_FontTexture);
    ImGui::GetIO().Fonts->TexID = 0;
    g_FontTexture.idx = BGFX_INVALID_HANDLE;
  }
}

void ImGui_Implbgfx_Init(int view) {
  g_View = (uint8_t)(view & 0xff);
}

void ImGui_Implbgfx_Shutdown() {
  ImGui_Implbgfx_InvalidateDeviceObjects();
}

void ImGui_Implbgfx_NewFrame() {
  if (!BGFX_HANDLE_IS_VALID(g_FontTexture)) {
    ImGui_Implbgfx_CreateDeviceObjects();
  }
}
