import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 800
    height: 680
    property alias gridWidth: grid.width

    property string ipAddress: "172.16.0.1"


    title: qsTr("DataBridge")

    //本工具是为了写数据接口

    header: ToolBar{

    }

    RowLayout{
        width: parent.width
        height: parent.height

        GridLayout {

            id: grid
            columns: 2
            Layout.fillHeight: true
            Layout.fillWidth: true


            width: 200
            clip: true




            Label {
                text: "IP"
            }

            ComboBox {
                textRole: "key"
                model: ListModel {
                    ListElement { key: "First"; value: 123 }
                    ListElement { key: "Second"; value: 456 }
                    ListElement { key: "Third"; value: 789 }
                }
            }

//            TextField{
//                id : ipAddressText
//                text: ipAddress
//                //inputMask: qsTr("")
//                font.family: "Microsoft YaHei"
//                font.pointSize: 12
//            }

            Label {
                text: "Port"
            }
            TextField{
                text: socketBridge.currentRecPort
            }


            Switch{
                Layout.columnSpan: 2
                text: "OK"
                onToggled: console.log(this.checked)
            }


        }



        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "#CCC"
        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "#CCC"

            TextArea{
                anchors.fill: parent
                text: "这里是数据"
            }

        }
    }

}
