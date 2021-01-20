import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: "QRayTracing"

    FileDialog {
        id: fileDialog
        title: "Choose a scene file"
        nameFilters: [ "Json files (*.json)", "All files (*)" ]
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            if (fileDialogOpenFiles.checked)
                filenameDisplay.text = fileUrls
        }
        onRejected: { console.log("Rejected") }
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"
            Action {
                text: "&Open..."
                onTriggered: fileDialog.open()
            }
            Action {
                text: "&Save..."
                //Implement me
            }
            Action {
                text: "&Save As"
                //Implement me
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
        }
    }

    Text {
        id: filenameDisplay
        text: "no file selected"
        anchors.bottom: parent.bottom
    }

    footer: TabBar {
        TabButton {
            text: "Render"
            //onClicked:
        }
    }
}
