import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Bunny image annotator V1.0")
    property  string datasetPath: "..."
    ListModel {
        id:mymodel

    }
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
        }

        Page2Form {
            id:form2
        }
        onCurrentIndexChanged: {
        form2.setDataSetPath(datasetPath)
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Settings")
        }
        TabButton {
            text: qsTr("Labeling")
        }

    }
}
