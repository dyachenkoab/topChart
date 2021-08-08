import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

Window {
    width: 1024
    height: 768
    visible: true
    title: qsTr("Most common words")

    Button {
        id: button
        text: "OPEN"
        width: parent.width / 17
        height: parent.height / 20
        anchors.left: parent.left
        anchors.top: parent.top
        onClicked: {
            bars.fileDialog.visible = true
        }
    }

    Bars {
        id: bars
        anchors.left: button.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Connections {
        target: postProcessing
        function onDone() {
           postProcessing.cleanUp()
           bars.progressBar.value = 0
           button.enabled = true
           bars.progressBar.visible = false
        }

        function onCurrentSize(sz) {
            bars.progressBar.value = sz;
        }

        function onFileSize(sz) {
            bars.progressBar.to = sz
        }

        function onReadyToOperate() {
            var l = postProcessing.returnKeys()
            var j = postProcessing.returnValues()
            var max = postProcessing.returnMax()

            bars.yAxis.max = max

            for (let i = 0; i < l.length; i++){
               bars.barSeries.append(l[i], [ j[i] ] );
            }
        }
    }
}
