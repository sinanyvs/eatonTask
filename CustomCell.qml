import QtQuick.Window 2.2
import QtQuick 2.0

Rectangle {

    width: 157; height: 120
    border.width: 1

    id: topStack

    property string titleVal: ""
    property string secondVal: ""
    property string thirdVal: ""

    color: "white"


    Rectangle{

        id: topRect
        width: 157
        height: parent.height/3

        anchors.top: parent.top
        color: "transparent"

        Text {
            id:title
            text: "ID:" + titleVal
            anchors.fill: parent;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignTop
            font.pixelSize: 15
            font.bold: true
        }
    }

    Rectangle{

        id: secondRect
        width: 147
        height: parent.height/3

        anchors.top: topRect.bottom
        anchors.right: parent.right
        color: "transparent"

        Text {
            id:val1
            text: "Voltage : " + secondVal + "V"
            anchors.fill: parent;
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignTop
            font.pixelSize: 13
            font.bold: false
            Behavior on  text{

                SequentialAnimation
                {
                    PropertyAnimation{
                        id:forward
                        target: topStack
                        properties: "color"
                        to: "green"
                        duration: 500

                    }

                    PropertyAnimation{
                        id:back
                        target: topStack
                        properties: "color"
                        to: "white"
                        duration: 500

                    }
                }
            }
        }
    }

    Rectangle{

        id: thirdRect
        width: 147
        height: parent.height/3

        anchors.top: secondRect.bottom
        anchors.right: parent.right
        color: "transparent"

        Text {
            id:val2
            text: "Current : " + thirdVal + "A"
            anchors.fill: parent;
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignTop
            font.pixelSize: 13
            font.bold: false
            Behavior on  text{

                SequentialAnimation
                {
                    PropertyAnimation{
                        id:forward1
                        target: topStack
                        properties: "color"
                        to: "green"
                        duration: 500

                    }

                    PropertyAnimation{
                        id:back1
                        target: topStack
                        properties: "color"
                        to: "white"
                        duration: 500

                    }
                }
            }
        }
    }
}
