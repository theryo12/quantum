#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>

// test fixture for initializing SDL
class SDLTest : public ::testing::Test {
protected:
    void SetUp() override {
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), 0) << "SDL initialization failed: " << SDL_GetError();
    }

    void TearDown() override {
        SDL_Quit();
    }
};

// test for SDL window creation
TEST_F(SDLTest, WindowCreation) {
    SDL_Window* window = SDL_CreateWindow(
        "Test Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    
    ASSERT_TRUE(window != nullptr) << "Failed to create SDL window: " << SDL_GetError();

    // simulate short delay before closing the window
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    SDL_DestroyWindow(window);  // clean up window after test
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 