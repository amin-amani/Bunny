import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
// FileDialog
import Qt.labs.folderlistmodel 2.1

// FolderListModel
Rectangle {

    property url path
    property int i: 0
    width: 600
    height: 400
    gradient: Gradient {
             GradientStop { position: 0.0; color: "black" }
             GradientStop { position: 1.0; color: "gray" }
         }

    FileDialog {
        id: photoDirectoryFileDialog
        title: "Select the photo directory:"
        selectFolder: true
        visible: false
        height: parent.height
        width: parent.width
        onAccepted: {
            //datasetPath = fileUrl
            processManager.setDatasetPath(fileUrl)
        }
    }
    Grid {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 100
        spacing: 10
        columns: 1
        rows: 4
        Button {
            height: 50
            width: 200
            background: Rectangle {

                   border.width: 1
                   border.color: "black"
                   radius: 4
               }
            onClicked: photoDirectoryFileDialog.visible = true
            text: "Brows dataset ..."
        }
        Label {

            height: 50
            width: 400
            text: qsTr(datasetPath)
        }
        Row {
            spacing: 10
            Button {
                text: "Add Class"
                background: Rectangle {

                       border.width: 1
                       border.color: "black"
                       radius: 4
                   }
                onClicked: {
                    mymodel.append({
                                       "name": classNameInput.text
                                   })
                    processManager.addClassifyClasses(classNameInput.text)
                    classNameInput.text = ""
                }
            }
            Rectangle {
                border.color: "gray"
                height: 40
                width: 100

                TextEdit {

                    anchors.centerIn: parent
                    id: classNameInput
                    width: 40
                }
            }
            Button {
                background: Rectangle {

                       border.width: 1
                       border.color: "black"
                       radius: 4
                   }
                text: "Clear List"
                onClicked: {
                    mymodel.clear()
                    processManager.remveClassifyClasses()
                }
            }

            Button {
                text: "save List"
                background: Rectangle {

                       border.width: 1
                       border.color: "black"
                       radius: 4
                   }
                onClicked: {

                    processManager.saveResult()
                }
            }
        }

        ListView {
            width: 180
            height: 200

            model: mymodel
            delegate: Text {
                text: name
            }
        }
    }
}
