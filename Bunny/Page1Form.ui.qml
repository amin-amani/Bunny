import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
// FileDialog
import Qt.labs.folderlistmodel 2.1

// FolderListModel
Page {

    property url path
    property int i: 0
    width: 600
    height: 400

    FileDialog {
        id: photoDirectoryFileDialog
        title: "Select the photo directory:"
        selectFolder: true
        visible: false
        height: parent.height
        width: parent.width
        onAccepted: {
            datasetPath = fileUrl
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
            onClicked: photoDirectoryFileDialog.visible = true
            text: "Brows dataset ..."
            //testImage.source ="file:"+"../NojhanImageAnotator/dataset/Perfect_Pistachio_clean146_1.jpg"
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
                text: "Clear List"
                onClicked: {
                    mymodel.clear()
                    processManager.remveClassifyClasses()
                }


            }

            Button {
                text: "save List"
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
