cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME WrenchEditor)
set(EXE_NAME wrench_editor)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILE_PATHS
    # Main
    src/main/main.cpp
    src/main/WrenchEditor.cpp
    src/main/FrameRate.cpp
    src/main/Renderer.cpp

    # Window
    #src/window/Window.cpp
    #src/window/MainWindow.cpp

    # Utils
    src/utils/sleep.cpp

    # Logging
    src/logging/logging.cpp

    # Widgets
    #src/widgets/SplitterWidget.cpp
    #src/widgets/ResizableContainerWidget.cpp
    #src/widgets/DraggablePanelWidget.cpp

    # Model (MVP)
    src/mvp/view/WrenchEditorCanvas.cpp
    src/mvp/view/WrenchEditorView.cpp
  
)

set(HEADERS
    # Main
    src/main/Config.h
    src/main/WrenchEditor.h
    src/main/FrameRate.h
    src/main/Renderer.h

    # Window
    include/wrench_editor/window/Window.h

    # Utils
    include/wrench_editor/utils/sleep.h

    # Logging
    include/wrench_editor/logging/logging.h

    # Memory
    include/wrench_editor/memory/Ref.h

    include/wrench_editor/IKeyHandler.h
    include/wrench_editor/IRenderer.h

    # Widgets
    #include/wrench_editor/widgets/SplitterWidget.h
    #include/wrench_editor/widgets/ResizableContainerWidget.h
    #include/wrench_editor/widgets/DraggablePanelWidget.h

    # View (MVP)
    include/wrench_editor/mvp/view/WrenchEditorCanvas.h
    include/wrench_editor/mvp/view/WrenchEditorView.h
)

set(WINDOWS_SOURCES
    #src/Platform/windows_file_dialog.cpp
)

set(LINUX_SOURCES
    #src/Platform/linux_file_dialog.cpp
)

include_directories(include)
add_executable(${EXE_NAME} ${SOURCE_FILE_PATHS} ${HEADERS})
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXE_NAME})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(${EXE_NAME} PRIVATE ${WINDOWS_SOURCES})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(${EXE_NAME} PRIVATE ${LINUX_SOURCES})
endif()

target_compile_definitions(${EXE_NAME}
    PRIVATE
        "FONT_ROOT_DIRECTORY=\"${CMAKE_SOURCE_DIR}/res/fonts/\""
)

set(RENDELL_UI_FONT_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR}/res/Fonts/)
add_subdirectory(rendell-stuff)
target_link_libraries(${EXE_NAME} PUBLIC rendell_stuff)
