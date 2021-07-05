import QtQuick 2.0
import QtQuick.Window 2.1

Window {
    id: aboutWin
    height: 200
    width: 500

    Column {
        spacing: 5
        Text {
            text: "QRayTracing"
        }
        Text {
            text: "See the README at https://github.com/kjosh9/QRayTracing"
        }
    }
}
