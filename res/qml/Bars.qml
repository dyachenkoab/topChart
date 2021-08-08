import QtQuick 2.0
import QtCharts 2.10
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.14

ChartView {
    property alias barSeries: barSeries
    property alias progressBar: progressBar
    property alias fileDialog: fileDialog
    property alias yAxis: yAxis
    signal setLink(link: string)

    id: chartView
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    Component.onCompleted: {
        setLink.connect(postProcessing.newComputation)
    }

    BarSeries {
        id: barSeries
        axisY:  ValueAxis {
             id: yAxis
             min: 0
             max: 3
        }
        axisX: BarCategoryAxis {
            categories: [ "Most common words" ]
        }
    }

    ProgressBar {
        id: progressBar
        visible: false
        from:0
        to: 0
        anchors.centerIn: parent
    }

    FileDialog {
        id: fileDialog
        visible: false
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            setLink(fileDialog.fileUrl)
            barSeries.clear()
            progressBar.visible = true
            button.enabled = false
        }
    }
}

