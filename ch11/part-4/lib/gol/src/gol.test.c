#include <unity.h>

#include <minimal-cmake-gol/gol.h>

void setUp(void) {
}

void tearDown(void) {
}

void test_create_gol_board(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  TEST_ASSERT_NOT_NULL(board);
  mc_gol_destroy_board(board);
}

void test_create_gol_board_of_size(void) {
  mc_gol_board_t* board = mc_gol_create_board(20, 30);
  const int32_t width = mc_gol_board_width(board);
  const int32_t height = mc_gol_board_height(board);
  TEST_ASSERT_EQUAL_INT32(20, width);
  TEST_ASSERT_EQUAL_INT32(30, height);
  mc_gol_destroy_board(board);
}

void test_initial_gol_board_cell_state(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  for (int y = 0, height = mc_gol_board_height(board); y < height; y++) {
    for (int x = 0, width = mc_gol_board_width(board); x < width; x++) {
      const bool cell = mc_gol_board_cell(board, x, y);
      TEST_ASSERT_FALSE(cell);
    }
  }
  mc_gol_destroy_board(board);
}

void test_set_gol_board_cell_state(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  for (int y = 0, height = mc_gol_board_height(board); y < height; y++) {
    for (int x = 0, width = mc_gol_board_width(board); x < width; x++) {
      mc_gol_set_board_cell(board, x, y, true);
      const bool cell = mc_gol_board_cell(board, x, y);
      TEST_ASSERT_TRUE(cell);
    }
  }
  mc_gol_destroy_board(board);
}

void test_cell_has_expected_number_of_live_neighbors(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  mc_gol_set_board_cell(board, 1, 0, true);
  mc_gol_set_board_cell(board, 1, 1, true);
  mc_gol_set_board_cell(board, 0, 1, true);
  {
    const int32_t alive = mc_gol_alive_neighbors(board, 0, 0);
    TEST_ASSERT_EQUAL_INT32(3, alive);
  }
  {
    const int32_t alive = mc_gol_alive_neighbors(board, 5, 5);
    TEST_ASSERT_EQUAL_INT32(0, alive);
  }
  mc_gol_destroy_board(board);
}

void test_cell_dies_with_fewer_than_two_alive_neighbors(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  mc_gol_set_board_cell(board, 1, 0, true);
  mc_gol_update_board(board);
  const bool cell = mc_gol_board_cell(board, 1, 0);
  TEST_ASSERT_FALSE(cell);
  mc_gol_destroy_board(board);
}

void test_cell_lives_with_two_alive_neighbors(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  mc_gol_set_board_cell(board, 0, 0, true);
  mc_gol_set_board_cell(board, 1, 0, true);
  mc_gol_set_board_cell(board, 2, 0, true);
  mc_gol_update_board(board);
  const bool cell = mc_gol_board_cell(board, 1, 0);
  TEST_ASSERT_TRUE(cell);
  mc_gol_destroy_board(board);
}

void test_cell_lives_with_three_alive_neighbors(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  mc_gol_set_board_cell(board, 0, 0, true);
  mc_gol_set_board_cell(board, 1, 0, true);
  mc_gol_set_board_cell(board, 1, 1, true);
  mc_gol_set_board_cell(board, 2, 0, true);
  mc_gol_update_board(board);
  const bool cell = mc_gol_board_cell(board, 1, 0);
  TEST_ASSERT_TRUE(cell);
  mc_gol_destroy_board(board);
}

void test_cell_dies_with_more_than_three_alive_neighbors(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  mc_gol_set_board_cell(board, 0, 0, true);
  mc_gol_set_board_cell(board, 0, 1, true);
  mc_gol_set_board_cell(board, 1, 0, true);
  mc_gol_set_board_cell(board, 1, 1, true);
  mc_gol_set_board_cell(board, 2, 0, true);
  mc_gol_update_board(board);
  const bool cell = mc_gol_board_cell(board, 1, 0);
  TEST_ASSERT_FALSE(cell);
  mc_gol_destroy_board(board);
}

void test_cell_resurrects_with_three_alive_neighbors(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  mc_gol_set_board_cell(board, 0, 0, true);
  mc_gol_set_board_cell(board, 1, 0, true);
  mc_gol_set_board_cell(board, 2, 0, true);
  mc_gol_update_board(board);
  const bool cell = mc_gol_board_cell(board, 1, 1);
  TEST_ASSERT_TRUE(cell);
  mc_gol_destroy_board(board);
}

void test_cell_neighbors_wrap_x_board(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  mc_gol_set_board_cell(board, 9, 0, true);
  mc_gol_set_board_cell(board, 9, 1, true);
  mc_gol_set_board_cell(board, 9, 2, true);
  const int32_t alive = mc_gol_alive_neighbors(board, 0, 1);
  TEST_ASSERT_EQUAL_INT32(3, alive);
  mc_gol_destroy_board(board);
}

void test_cell_neighbors_wrap_y_board(void) {
  mc_gol_board_t* board = mc_gol_create_board(10, 10);
  mc_gol_set_board_cell(board, 0, 9, true);
  mc_gol_set_board_cell(board, 1, 9, true);
  mc_gol_set_board_cell(board, 2, 9, true);
  const int32_t alive = mc_gol_alive_neighbors(board, 1, 0);
  TEST_ASSERT_EQUAL_INT32(3, alive);
  mc_gol_destroy_board(board);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_create_gol_board);
  RUN_TEST(test_create_gol_board_of_size);
  RUN_TEST(test_initial_gol_board_cell_state);
  RUN_TEST(test_set_gol_board_cell_state);
  RUN_TEST(test_cell_has_expected_number_of_live_neighbors);
  RUN_TEST(test_cell_dies_with_fewer_than_two_alive_neighbors);
  RUN_TEST(test_cell_lives_with_two_alive_neighbors);
  RUN_TEST(test_cell_lives_with_three_alive_neighbors);
  RUN_TEST(test_cell_dies_with_more_than_three_alive_neighbors);
  RUN_TEST(test_cell_resurrects_with_three_alive_neighbors);
  RUN_TEST(test_cell_neighbors_wrap_x_board);
  RUN_TEST(test_cell_neighbors_wrap_y_board);
  return UNITY_END();
}
