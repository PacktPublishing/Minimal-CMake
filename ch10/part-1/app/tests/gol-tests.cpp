#include <imgui_te_context.h>
#include <imgui_te_engine.h>
#include <minimal-cmake-gol/gol.h>

void RegisterGolTests(ImGuiTestEngine* e, mc_gol_board_t* board) {
  ImGuiTest* t = nullptr;
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

  t = IM_REGISTER_TEST(e, "gol-tests", "Restart simulation");
  t->TestFunc = [](ImGuiTestContext* ctx) {
    ctx->SetRef("Game of Life");
    ctx->ItemClick("Pause");
    ctx->ItemClick("Restart");
  };

  t = IM_REGISTER_TEST(e, "gol-tests", "Clear simulation");
  t->TestFunc = [](ImGuiTestContext* ctx) {
    ctx->SetRef("Game of Life");
    ctx->ItemClick("Clear");
  };

  t = IM_REGISTER_TEST(e, "gol-tests", "Click board");
  t->UserData = board;
  t->TestFunc = [](ImGuiTestContext* ctx) {
    const mc_gol_board_t* board = (mc_gol_board_t*)ctx->Test->UserData;
    ctx->SetRef("Game of Life");
    ctx->MouseMoveToPos(ImVec2(200, 200));
    ctx->MouseClick(ImGuiMouseButton_Left);
    ctx->MouseMoveToPos(ImVec2(400, 200));
    ctx->MouseClick(ImGuiMouseButton_Left);
    IM_CHECK_EQ(mc_gol_board_cell(board, 6, 6), true);
    IM_CHECK_EQ(mc_gol_board_cell(board, 19, 6), true);
  };
}
