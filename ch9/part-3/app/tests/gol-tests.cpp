#include <imgui_te_context.h>
#include <imgui_te_engine.h>

void RegisterGolTests(ImGuiTestEngine* e) {
  ImGuiTest* t = NULL;
  t = IM_REGISTER_TEST(e, "gol-tests", "Pause simulation");
  t->TestFunc = [](ImGuiTestContext* ctx) {
    ctx->SetRef("Game of Life");
    ctx->ItemClick("Pause");
  };
  t = IM_REGISTER_TEST(e, "gol-tests", "Play simulation");
  t->TestFunc = [](ImGuiTestContext* ctx) {
    ctx->SetRef("Game of Life");
    ctx->ItemClick("Play");
  };
  t = IM_REGISTER_TEST(e, "gol-tests", "Reset simulation");
  t->TestFunc = [](ImGuiTestContext* ctx) {
    ctx->SetRef("Game of Life");
    ctx->ItemClick("Pause");
    ctx->ItemClick("Reset");
  };
  t = IM_REGISTER_TEST(e, "gol-tests", "Clear simulation");
  t->TestFunc = [](ImGuiTestContext* ctx) {
    ctx->SetRef("Game of Life");
    ctx->ItemClick("Clear");
  };
  t = IM_REGISTER_TEST(e, "gol-tests", "Click board");
  t->TestFunc = [](ImGuiTestContext* ctx) {
    ctx->SetRef("Game of Life");
    ctx->MouseMoveToPos(ImVec2(200, 200));
    ctx->MouseClick(ImGuiMouseButton_Left);
  };
}
