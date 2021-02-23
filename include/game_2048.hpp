#ifndef GAME_2048_HPP
#define GAME_2048_HPP

#include <vector>

// CONFIGURATION OF GAME
namespace GAME2048
{
    const unsigned cMaxBlock = 2048;
    const unsigned cSizeX = 5;
    const unsigned cSizeY = 5;
    const unsigned cNewBlocksCount = 2;
} // namespace Game_2048


class Game_2048
{
  public:

    Game_2048();

    Game_2048(const Game_2048& ) = delete;

    Game_2048(const Game_2048&& ) = delete;

    Game_2048& operator=(Game_2048&& ) = delete;

    Game_2048& operator=(const Game_2048& ) = delete;

    ~Game_2048();

    void begin(); // start

  private:

    void showField() const ;

    char getAction() const;

    void changeWorld(char action);

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();

    bool newBlocks();

    void end();

    std::vector<std::vector<unsigned>> field_;
    unsigned score_;
    unsigned maxBlock_;
    unsigned maxX_;
    unsigned maxY_;
};

#endif // GAME_2048_HPP
