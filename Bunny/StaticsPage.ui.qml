import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
import Qt.labs.folderlistmodel 2.1
import QtCharts 2.0

Page {
    function chartAddSeires(name, value) {

        pieSeries.append(name, value)
    }
    function chartClear() {

        pieSeries.clear()
    }

    function showMerics(text) {
        metrictext.text = text
    }
    Column {
        spacing: 5
        anchors.centerIn: parent
        ChartView {
            width: 400
            height: 300
            theme: ChartView.ChartThemeBrownSand
            antialiasing: true

            PieSeries {
                id: pieSeries
            }
        }
        Text {

            id: metrictext
            anchors.margins: 10
            text: qsTr("...")
        }
    }
}
