cmake_minimum_required(VERSION 3.20)
project(Calculator)

# статическая линковка стандартных библиотек (для MinGW)
# ходят легенды что это поможет просто запускать файл.ехе с плагинами и всё будет работать автономно
if (MINGW)
    add_link_options(-static-libgcc -static-libstdc++ -static)
endif()

set(CMAKE_CXX_STANDARD 20)

# сборка экзешника
add_executable(Calculator
        main.cpp
        Tokenizator.cpp
        Parser.cpp
        NodeParser.cpp
        PluginLoader.cpp
)

# сборка dll
add_library(plugin_sin SHARED plugin_sin.cpp)
add_library(plugin_cos SHARED plugin_cos.cpp)
add_library(plugin_ln SHARED plugin_ln.cpp)

# куда вставить готовые dll
add_custom_command(TARGET Calculator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Calculator>/plugins"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:plugin_sin>" "$<TARGET_FILE_DIR:Calculator>/plugins"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:plugin_cos>" "$<TARGET_FILE_DIR:Calculator>/plugins"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:plugin_ln>" "$<TARGET_FILE_DIR:Calculator>/plugins"
)