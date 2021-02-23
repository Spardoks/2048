#include <ctime>
#include <cstdlib>
#include <iostream>
#include <limits>

#include "game_2048.hpp"

Game_2048::Game_2048()
    : field_(GAME2048::cSizeX,std::vector<unsigned>(GAME2048::cSizeY, 0))
    , score_(0)
    , maxBlock_(0)
    , maxX_(GAME2048::cSizeX)
    , maxY_(GAME2048::cSizeY)
{
    std::srand(std::time(nullptr));
}



Game_2048::~Game_2048()
{
}



void Game_2048::begin()
{
    bool newBlocksAdded = newBlocks();
    bool end = !newBlocksAdded || (maxBlock_ == GAME2048::cMaxBlock);
    showField();

    while(!end) {
        char action = getAction();
        changeWorld(action);
        newBlocksAdded = newBlocks();
        showField();
        end = !newBlocksAdded || (maxBlock_ == GAME2048::cMaxBlock);
    }

    this->end();
}



bool Game_2048::newBlocks()
{
    std::vector<unsigned*> emptyBlocks;
    for (unsigned i = 0; i < maxX_; ++i) {
        for (unsigned j = 0; j < maxY_; ++j) {
            if (field_[i][j] == 0){
                emptyBlocks.push_back(&field_[i][j]);
            }
        }
    }

    unsigned emptyCount = emptyBlocks.size();
    if (emptyCount < GAME2048::cNewBlocksCount) {
        return false;
    }

    for (unsigned i = 0; i < GAME2048::cNewBlocksCount; ++i) {
        unsigned posNewBlock = std::rand() % emptyCount;
        while (*emptyBlocks[posNewBlock] != 0) {
            posNewBlock += 1;
            posNewBlock %= emptyCount;
        }
        *emptyBlocks[posNewBlock] = ( ( std::rand() % 5 ) > 0 ) ? 2 : 4  ;
    }

    return true;
}



void Game_2048::showField() const
{
    // system("clear"); //system("cls");
    std::cout << std::endl;
    for (unsigned i = 0; i < maxY_; ++i) {
        for (unsigned j = 0; j < maxX_; ++j) {
            // 5 chars to 1 block
            switch(field_[i][j]) {
                case 0: std::cout << "*    "; break;
                case 2: std::cout << "2    "; break;
                case 4: std::cout << "4    "; break;
                case 8: std::cout << "8    "; break;
                case 16: std::cout << "16   "; break;
                case 32: std::cout << "32   "; break;
                case 64: std::cout << "64   "; break;
                case 128: std::cout << "128  "; break;
                case 256: std::cout << "256  "; break;
                case 512: std::cout << "512  "; break;
                case 1024: std::cout << "1024 "; break;
                case 2048: std::cout << "2048 "; break;
                default: std::cout << "Ooops, smth badly!"; exit(-1);
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\nSCORE: " << score_ << "\nMAX_BLOCK: " << maxBlock_ << "\nw, a, s, d" <<  std::endl;
}



char Game_2048::getAction() const
{

    char action = '\0';
    bool goodInput = false;
    do {
        if (std::cin.peek() == '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        action = std::cin.get();

        if ( !std::cin.fail() ) {
            if ( (action == 'a') || (action == 'd') ||
                 (action == 's') || (action == 'w') ) {
                goodInput = true;
            }
        } else {
            action = '\0';
            std::cin.clear();
        }
        if (std::cin.peek() != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goodInput = false;
        }
    } while (!goodInput);

    return action;
}



void Game_2048::changeWorld(char action)
{
    switch(action) {
        case 'a':
            moveLeft();
            break;
        case 's':
            moveDown();
            break;
        case 'd':
            moveRight();
            break;
        case 'w':
            moveUp();
            break;
        default :
            break;
    }
}



void Game_2048::moveLeft()
{
    for (unsigned i = 0; i < maxY_; ++i) {
        bool merged = false; // merged in this string
        for (unsigned j = 1; j < maxX_; ++j) {
            if (field_[i][j] != 0) {
                unsigned k = j;
                unsigned currentValue = field_[i][j];
                while ((k > 0) && (field_[i][k - 1] == 0)) {
                    --k;
                }
                if (k == 0) {
                    field_[i][j] = 0;
                    field_[i][k] = currentValue;
                } else {
                    // field_[i][k - 1] > 0
                    if (!merged && (field_[i][k - 1] == currentValue)) {
                        // Merging
                        field_[i][j] = 0;
                        field_[i][k - 1] += currentValue;
                        merged = true;
                        score_ += currentValue;
                        if (field_[i][k - 1] > maxBlock_) {
                            maxBlock_ = field_[i][k - 1];
                        }
                    } else {
                        // already merged or field_[i][k - 1] != currentValue
                        field_[i][j] = 0;
                        field_[i][k] = currentValue;
                    }
                }
            }
        }
    }
}



void Game_2048::moveRight()
{
    for (unsigned i = 0; i < maxY_; ++i) {
        bool merged = false; // merged in this string
        unsigned j = maxX_ - 1;
        do {
            --j;
            if (field_[i][j] != 0) {
                unsigned k = j;
                unsigned currentValue = field_[i][j];
                while ((k < maxX_ - 1) && (field_[i][k + 1] == 0)) {
                    ++k;
                }
                if (k == (maxX_ - 1)) {
                    field_[i][j] = 0;
                    field_[i][k] = currentValue;
                } else {
                    // field_[i][k + 1] > 0
                    if (!merged && (field_[i][k + 1] == currentValue)) {
                        field_[i][j] = 0;
                        field_[i][k + 1] += currentValue;
                        merged = true;
                        score_ += currentValue;
                        if (field_[i][k + 1] > maxBlock_) {
                            maxBlock_ = field_[i][k + 1];
                        }
                    } else {
                        // already merged or field_[i][k + 1] != currentValue
                        field_[i][j] = 0;
                        field_[i][k] = currentValue;
                    }
                }
            }
        } while (j > 0);
    }
}



void Game_2048::moveDown()
{
    for (unsigned j = 0; j < maxX_; ++j) {
        bool merged = false; // merged in this string
        unsigned i = maxY_ - 1;
        do {
            --i;
            if (field_[i][j] != 0) {
                unsigned k = i;
                unsigned currentValue = field_[i][j];
                while ((k < maxY_ - 1) && (field_[k + 1][j] == 0)) {
                    ++k;
                }
                if (k == maxY_ - 1) {
                    field_[i][j] = 0;
                    field_[k][j] = currentValue;
                } else {
                    // field_[k + 1][j] > 0
                    if (!merged && (field_[k + 1][j] == currentValue)) {
                        field_[i][j] = 0;
                        field_[k + 1][j] += currentValue;
                        merged = true;
                        score_ += currentValue;
                        if (field_[k + 1][j] > maxBlock_) {
                            maxBlock_ = field_[k + 1][j];
                        }
                    } else {
                        // already merged or field_[k + 1][j] != currentValue
                        field_[i][j] = 0;
                        field_[k][j] = currentValue;
                    }
                }
            }
        } while (i > 0);
    }
}



void Game_2048::moveUp()
{
    for (unsigned j = 0; j < maxX_; ++j) {
        bool merged = false; // merged in this string
        for (unsigned i = 1; i < maxY_; ++i) {
            if (field_[i][j] != 0) {
                unsigned k = i;
                unsigned currentValue = field_[i][j];
                while ((k > 0) && (field_[k - 1][j] == 0)) {
                    --k;
                }
                if (k == 0) {
                    field_[i][j] = 0;
                    field_[k][j] = currentValue;
                } else {
                    // field_[k - 1][j] > 0
                    if (!merged && (field_[k - 1][j] == currentValue)) {
                        field_[i][j] = 0;
                        field_[k - 1][j] += currentValue;
                        merged = true;
                        score_ += currentValue;
                        if (field_[k - 1][j] > maxBlock_) {
                            maxBlock_ = field_[k - 1][j];
                        }
                    } else {
                        // already merged or field_[k - 1][j] != currentValue
                        field_[i][j] = 0;
                        field_[k][j] = currentValue;
                    }
                }
            }
        }
    }
}



void Game_2048::end()
{

    // system("clear"); //system("cls");
    std::cout << "\nGame Over!\nYour score: " << score_ << "\nYour maxBlock: " << maxBlock_ << '\n';
    std::cin.get();
}
