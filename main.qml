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
    signal saveFile(msg: string)

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
            /*
            Action {
                text: "&Save"
            }
            */
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
            Action { text: qsTr("&About") }
            //Implement me
        }
    }

    Item {
        id: image_area
        anchors.top: menu_bar.bottom
        anchors.bottom: filename_display.top
        anchors.right: root.right
        anchors.left: root.left
        Image {
            id: rendered_image
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "image://rendered_image/scene_0.json"
        }
    }

    Text {
        id: filename_display
        anchors.bottom: render_button.top
        text: (root.scene_filename.length > 0) ? root.scene_filename : "no file selected"
    }

    RoundButton {
        id: render_button
        anchors.horizontalCenter: root.horizontalCenter
        anchors.bottom: root.bottom
        text: "Render"
        radius: 15
        onClicked: {
            rendered_image.source = "image://rendered_image/" + root.scene_filename
        }
    }
}

