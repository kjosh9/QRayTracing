cmake_minimum_required(VERSION 3.1.0)

project(QRayTracing VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)

include_directories(${Qt5Core_INCLUDES})
add_definitions(${Qt5Core_DEFINITIONS})

qt5_add_resources(RESOURCES qml.qrc)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_subdirectory(core)

add_executable(QRayTracing
    main.cpp
    parse.cpp
    imageprovider.cpp
    renderedimageresponse.cpp
    imagerenderrunnable.cpp
    ${RESOURCES}
)

qt5_use_modules(QRayTracing Quick Core Gui Qml)

target_link_libraries(QRayTracing
    core
    Qt5::Core
    Qt5::Qml
    Qt5::Gui
    Qt5::Quick
)
