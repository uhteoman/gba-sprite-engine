project(SonicEscape)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/StartScreen.cpp
        src/StartScreen.h
        src/startscreenbg.h
        src/Gamescene.cpp
        src/Gamescene.h
        src/sonicdata.h
        src/sonic.cpp
        src/sonic.h src/blockdata.h src/Block.cpp src/Block.h src/gamescenebg.h src/seashanty.h src/shared.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
