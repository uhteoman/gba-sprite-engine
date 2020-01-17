//
// Created by Teoman on 28/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_STARTSCREEN_H
#define GBA_SPRITE_ENGINE_PROJECT_STARTSCREEN_H

#include <libgba-sprite-engine/scene.h>

using namespace std;

class StartScreen : public Scene {
private:
    unique_ptr<Background> bg;
    unique_ptr<Sprite> sonic;

public:
    StartScreen(const shared_ptr<GBAEngine> &engine);
    vector<Sprite *> sprites() override;
    vector<Background *> backgrounds() override;
    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_STARTSCREEN_H
