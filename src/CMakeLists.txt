set(SOURCES main.cpp
            game.cpp
            shader.cpp
            texture2d.cpp
            resourcemanager.cpp
            spriterenderer.cpp
            gameobject.cpp
            gamelevel.cpp
)

add_library(main_obj OBJECT ${SOURCES})