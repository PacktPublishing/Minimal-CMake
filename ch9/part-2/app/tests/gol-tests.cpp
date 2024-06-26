#include <imgui_te_engine.h>
#include <imgui_te_context.h>

void RegisterGolTests(ImGuiTestEngine* e) {
  ImGuiTest* t = NULL;
  t = IM_REGISTER_TEST(e, "demo_tests", "test1");
  t->TestFunc = [](ImGuiTestContext* ctx) {
    ctx->SetRef("Dear ImGui Demo");
    ctx->MenuCheck("Tools/Metrics\\/Debugger");
  };
}
