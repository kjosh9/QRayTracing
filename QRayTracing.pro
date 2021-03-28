QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        core/color.cpp \
        core/renderer.cpp \
        gui/image_provider.cpp \
        main.cpp \
        core/camera.cpp \
        core/light.cpp \
        core/plane.cpp \
        core/point3d.cpp \
        core/shadedObject.cpp \
        core/scene.cpp \
        core/sphere.cpp \
        core/parse.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

HEADERS += \
    core/camera.hpp \
    core/color.hpp \
    core/light.hpp \
    core/plane.hpp \
    core/point3d.hpp \
    core/renderer.hpp \
    core/scene.hpp \
    core/sphere.hpp \
    core/shadedObject.hpp \
    gui/image_provider.hpp \
    core/parse.hpp
