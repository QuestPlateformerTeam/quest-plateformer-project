cmake_minimum_required(VERSION 3.10)
project(QuestPlateformer)

set(CMAKE_CXX_STANDARD 17)

# Inclure les headers du projet
include_directories(include)

# Inclure les headers SFML
include_directories("C:/Users/Alexi/Documents/SFML-2.5.1/include")

# Récupérer tous les fichiers sources
file(GLOB_RECURSE SOURCES
        src/*.cpp
        main.cpp
)

# Créer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Définir le chemin vers SFML
set(SFML_DIR "C:/Users/Alexi/Documents/SFML-2.5.1/lib/cmake/SFML")

# Chercher SFML (version dynamique)
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Lier SFML
target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
)

# Définir les DLL à copier automatiquement
if(WIN32)
    set(SFML_DLLS
            "C:/Users/Alexi/Documents/SFML-2.5.1/bin/sfml-system-d-2.dll"
            "C:/Users/Alexi/Documents/SFML-2.5.1/bin/sfml-window-d-2.dll"
            "C:/Users/Alexi/Documents/SFML-2.5.1/bin/sfml-graphics-d-2.dll"
            "C:/Users/Alexi/Documents/SFML-2.5.1/bin/sfml-audio-d-2.dll"
    )

    # Ajouter une commande post-build pour copier toutes les DLL
    foreach(dll ${SFML_DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${dll} $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endforeach()
endif()
