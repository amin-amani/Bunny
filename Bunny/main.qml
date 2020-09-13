import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    visible: true
    width: 640
    height: 600

    //title: qsTr("Bunny image annotator V1.0")
    property  string datasetPath: "..."
    function chartAddSeries(name,value)

    {
        staticPage.chartAddSeires(name,value)
    }
    function chartClear()

    {
        staticPage.chartClear()
    }

    function showChartMetrics(text)
    {
        staticPage.showMerics(text)

    }
    function setDatasetAddress(path)
    {
        datasetPath=path
        form2.setDataSetPath(path)

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
    function showToast(label,delay)
    {
        toastText.text=label
        toast.visible=true
        toastTimer.interval=delay
        toastTimer.start();
    }
    Timer
    {
        id: toastTimer
        onTriggered: toast.visible=false
    }
    Rectangle
    {
        visible: false
        id:toast
        radius: 5
        z:10
        width:  parent.width/2
        height: parent.height/16


        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom
        color: "gray";
        Text {
            id: toastText
            anchors.centerIn: parent
            color: "white"
            text: qsTr("toas")
        }
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
        StaticsPage {

            id:staticPage
        }
        onCurrentIndexChanged: {
            form2.setDataSetPath(datasetPath)
        }
    }

        Button {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            text: qsTr("<")
                width: 100
                height: 50
                onClicked: {

                    swipeView.currentIndex--
                if(swipeView.currentIndex<0)swipeView.currentIndex=0
                }

        }

        Button {
            width: 100
            height: 50
            anchors.right:  parent.right
            anchors.bottom: parent.bottom
            text: qsTr(">")
            onClicked: {

                swipeView.currentIndex++
             if(swipeView.currentIndex>2)swipeView.currentIndex=2
            }
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
//}

