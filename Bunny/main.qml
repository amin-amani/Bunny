import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    visible: true
    width: 640
    height: 480

    //title: qsTr("Bunny image annotator V1.0")
    property  string datasetPath: "..."


    function setDatasetAddress(path)
    {
            datasetPath=path
          form2.setDataSetPath(path)
           console.log(datasetPath)
    }
    function addToModel(value)
    {
        mymodel.append({
                           "name": value
                       })

    }

    function displayImage(src)
    {
    form2.displayImage(src)
    }
    function setImageLabel(label)
    {
    form2.setImageLabel(label)
    }
    ListModel {
        id:mymodel

    }
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex:0// tabBar.currentIndex
        focus: true
        Keys.onPressed: {
            processManager.keyHandler(event.key)
           // console.log(event.key)
                }
        Page1Form {


        }

        Page2Form {
            id:form2

        }
        onCurrentIndexChanged: {
            form2.setDataSetPath(datasetPath)
        }
    }

//    footer: TabBar {
//        id: tabBar
//        currentIndex: swipeView.currentIndex

//        TabButton {
//            text: qsTr("Settings")


//        }
//        TabButton {
//            text: qsTr("Labeling")
//        }
//        onCurrentIndexChanged: swipeView.focus= true

//    }
}

