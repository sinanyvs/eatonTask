import QtQuick 2.12
import QtQuick.Window 2.12
import sinan.examples.Receiver 1.0

Window {

    id:root
    width: 640
    height: 500
    visible: true
    title: qsTr("Device Monitoring")

    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    Receiver{
        id:rx
    }


    Rectangle{
        id:info
        height: 20
        width: parent.width
        anchors.top: parent.top
        anchors.bottomMargin: 2
        border.width: 1

        Text {
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            leftPadding: 5
            font.pixelSize: 13
            text: "Total Valid Message Received : " + rx.validMessageCount + " Total Invalid Message Received : " + rx.invalidMessageCount + " Number of Device : " + rx.numOfDevice
        }
    }

    Rectangle{

        anchors.top: info.bottom
        width: parent.width
        height: parent.height

        Flickable
        {
            anchors.fill: parent
            contentHeight: mainTable.height
            contentWidth: mainTable.width
            clip:  true

            Grid {

                id:mainTable
                columns: 4
                spacing: 4

                Repeater{

                    model:rx.numOfDevice

                    CustomCell{

                        titleVal: rx.idList[index]
                        secondVal: rx.voltageList[index]
                        thirdVal: rx.currentList[index]
                    }
                }
            }
        }
    }
}
