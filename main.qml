import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0
import QtQuick 2.15

Item {
    id: root
    height: 1200
    width: 1200
    visible: true
    property string scene_filename
    signal saveFileNoName()
    signal saveFile(string filename)
    signal setThreadCount(int threads)
    property variant about_win;

    FileDialog {
        id: open_dialog
        title: "Choose a scene file"
        nameFilters: [ "Json files (*.json)", "All files (*)" ]
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            root.scene_filename = fileUrl
        }
    }

    FileDialog {
        id: save_dialog
        title: "Save image"
        nameFilters: ["*.jpeg", "All files(*)"]
        selectExisting: false
        onAccepted: {
            console.log("Selected to save: " + fileUrls)
            root.saveFile(fileUrl)
        }
    }

    MenuBar {
        id: menu_bar
        anchors.top: root.top
        Menu {
            title: "&File"
            Action {
                text: "&Open"
                onTriggered: open_dialog.open()
            }
            Action {
                text: "&Save"
                onTriggered: root.saveFileNoName()
            }
            Action {
                text: "&Save As"
                onTriggered: save_dialog.open()
            }
            MenuSeparator { }
            Action {
                text: "&Quit"
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: "&Help"
            Action {
                text: qsTr("&About")
                onTriggered: {
                    var about_comp = Qt.createComponent("aboutWindow.qml");
                    about_win = about_comp.createObject(root);
                    about_win.show();
                }
            }
        }
    }

    Row {
        id: renderBar
        anchors.top: menu_bar.bottom
        anchors.topMargin: 10
        anchors.left: root.left
        anchors.leftMargin: 10
        spacing: 10

        ComboBox {
            currentIndex: 2
            model: ListModel {
                id: threadsBox
                ListElement {text: "1"}
                ListElement {text: "2"}
                ListElement {text: "4"}
                ListElement {text: "6"}
                ListElement {text: "8"}
                ListElement {text: "10"}
                ListElement {text: "12"}
                ListElement {text: "14"}
                ListElement {text: "16"}
                ListElement {text: "24"}
                ListElement {text: "32"}
            }
            width: 100
            onCurrentIndexChanged: {
                root.setThreadCount(parseInt(threadsBox.get(currentIndex).text));
            }
        }

        RoundButton {
            id: render_button
            text: "Render"
            radius: 5
            onClicked: {
                rendered_image.source = "image://rendered_image/" + root.scene_filename
            }
            enabled: root.scene_filename.length > 0
        }
        Text {
            id: filename_display
            text: (root.scene_filename.length > 0) ? root.scene_filename : "no file selected"
            anchors.bottom: render_button.bottom
        }
    }
    Item {
        id: image_area
        anchors.top: renderBar.bottom
        anchors.bottom: root.bottom
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter

        Rectangle {
            anchors.fill: parent
            border.color: "black"
            border.width: 1
        }

        Image {
            id: rendered_image
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "image://rendered_image/scene_0.json"
        }

        Item {
            id: rendering_prompt
            anchors.centerIn: parent
            visible: rendered_image.progress != 1
            AnimatedImage {
                id: rotating_gear
                anchors.centerIn: parent
                source: "rotating_gear.gif"
            }

            Text {
                id: rendering_text
                anchors.top: rotating_gear.bottom
                anchors.topMargin: 50
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Rendering...")
            }
        }
    }
}

