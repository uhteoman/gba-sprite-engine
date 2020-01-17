//
// Created by Teoman on 11/12/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAMESCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_GAMESCENE_H
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/background.h>
#include "sonic.h"
#include "Block.h"


class Gamescene : public Scene{
private:
    int score = 0;
    std::unique_ptr<Sprite> sonic;
    std::unique_ptr<Sprite> block;
    std::unique_ptr<Sprite> secondBlock;
    std::unique_ptr<Background> bg;
    std::unique_ptr<Sonic> sonicModel;
    std::unique_ptr<Block> blockModel;
    std::unique_ptr<Block> secondBlockModel;
    int scrollX;
    int isOnPlatform =0;
public:
    Gamescene(std::shared_ptr<GBAEngine> engine): Scene(engine), scrollX(0) {}
    std::vector<Sprite*> sprites() override;
    std::vector<Background*> backgrounds() override;
    int getIsOnPlatform();
    void resetGame();
    void fallDown();
    void followPlatform();
    void load() override;
    void tick(u16 keys) override;

};



#endif //GBA_SPRITE_ENGINE_PROJECT_GAMESCENE_H
