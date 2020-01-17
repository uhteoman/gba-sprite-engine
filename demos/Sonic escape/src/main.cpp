//
// Created by Teoman on 28/11/2019.
//
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "StartScreen.h"
int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    auto scene = new StartScreen(engine);
    engine->setScene(scene);

    while (true) {
        engine->update();
        //engine->delay(1000);
    }
    return 0;
}
