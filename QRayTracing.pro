QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        renderer.cpp \
        camera.cpp \
        light.cpp \
        plane.cpp \
        point3d.cpp \
        shadedObject.cpp \
        scene.cpp \
        sphere.cpp

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
    renderer.hpp \
    camera.hpp \
    light.hpp \
    plane.hpp \
    point3d.hpp \
    scene.hpp \
    sphere.hpp \
    shadedObject.hpp
