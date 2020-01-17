//
// Created by Teoman on 28/11/2019.
//
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "StartScreen.h"
#include "startscreenbg.h"
#include "Gamescene.h"
#include "sonicdata.h"
#include "shared.h"
#include "startscreenmusic.h"

StartScreen::StartScreen(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> StartScreen::sprites() {
    return {sonic.get()};
}

std::vector<Background *> StartScreen::backgrounds() {
    return {
            bg.get()
    };
}
void StartScreen::tick(u16 keys) {
    if(keys & KEY_START) {
        engine->transitionIntoScene(new Gamescene(engine), new FadeOutScene(2));
    }
}

void StartScreen::load() {
    engine.get()->disableText();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(paletteSharedPal, sizeof(paletteSharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(startscreenimagePal, sizeof(startscreenimagePal)));

    SpriteBuilder<Sprite> builder;
    sonic = builder
            .withData(sonicTiles, sizeof(sonicTiles))
            .withSize(SIZE_32_32)
            .withAnimated(0,2,15)
            .withLocation(20, 40)
            .buildPtr();

    bg = std::unique_ptr<Background>(new Background(0, startscreenimageTiles, sizeof(startscreenimageTiles), startscreenimageMap, sizeof(startscreenimageMap)));
    bg.get()->useMapScreenBlock(24);

    engine->enqueueMusic(parks, sizeof(parks), 16000);
}

