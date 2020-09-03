import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
// FileDialog
import Qt.labs.folderlistmodel 2.1

// FolderListModel
Page {

    width: 600
    height: 400

    property string path: ""
    property int i: 0
    function setDataSetPath(msg) {
        folderModel.folder=msg
        console.log(folderModel.columnCount())
        path=msg;
    }
    function buttonPressed(btn)
    {
        console.log(btn)


        testImage.source = path + "/" + folderModel.get(
                    i, "fileName")
        i = i + 1

    }


    ListView {

        FolderListModel {
            id: folderModel
            //folder: datasetPath
            nameFilters: ["*.jpg"]
            onFolderChanged:     testImage.source = path + "/" + folderModel.get(
                                     0, "fileName")
        }


        model: folderModel


    }


    BorderImage{
        id: testImage
        anchors.centerIn: parent
        source: "images/bugs_bunny.jpeg"

        MouseArea {
            anchors.fill: parent
            onClicked: {

//                testImage.source = path + "/" + folderModel.get(
//                            i, "fileName")
//                i = i + 1
            }
        }
    }

    Grid
    {

        anchors.margins: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom:  parent.bottom
        spacing: 10
        Repeater {
            model: mymodel.count
            Button{
                text: mymodel.get(index).name
                onClicked: buttonPressed(mymodel.get(index).name)
            }
        }


    }

}
