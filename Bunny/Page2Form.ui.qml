import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
import Qt.labs.folderlistmodel 2.1

Page {

    width: 600
    height: 400

    property string path: ""
    property int i: 0
    //property list<Item> lables
    property variant userLables: [100000]

    //------------------------------------------------------------------
    function displayImage(src) {
        classifyImage.source = src
    }
    function setImageLabel(label) {
        imageLable.text = label
    }
    //    function nextImage() {

    //        if(mymodel.count<1)return
    //        console.log("next")
    //        i = i + 1
    //        testImage.source = path + "/" + folderModel.get(i, "fileName")
    //        //imageLable.text=mymodel[userLables[i]]
    //        console.log(userLables[i])

    //    }

    //    function prevImage() {
    //        if(mymodel.count<1)return
    //        console.log("prev")
    //        i = i - 1
    //        testImage.source = path + "/" + folderModel.get(i, "fileName")
    //        //imageLable.text=mymodel[userLables[i]]
    //      console.log(userLables[i])
    //    }
    function setClass(x) {

        console.log("class " + (x - 48))
        userLables[i] = x - 48
    }
    function setDataSetPath(msg) {
        folderModel.folder = msg
        console.log(folderModel.columnCount())
        path = msg
    }

    //------------------------------------------------------------------
    ListView {

        FolderListModel {
            id: folderModel
            //folder: datasetPath
            nameFilters: ["*.jpg"]
            //onFolderChanged: testImage.source = path + "/" + folderModel.get(0, "fileName")
        }

        model: folderModel
    }

    BorderImage {
        id: classifyImage
        anchors.centerIn: parent
        source: "images/bugs_bunny.jpeg"
        Text {
            id: imageLable
            anchors.bottom: parent.top
            text: qsTr("NC")
            font.pointSize: 12
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {

                //                testImage.source = path + "/" + folderModel.get(
                //                            i, "fileName")
                //                i = i + 1
            }
        }
    }

    Grid {

        anchors.margins: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        spacing: 10
        Repeater {
            model: mymodel.count
            Button {
                text: mymodel.get(index).name
                onClicked: processManager.classifyButtonClicked(
                               mymodel.get(
                                   index).name) //buttonPressed(mymodel.get(index).name)
            }
        }
    }
}
