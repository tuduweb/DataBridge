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
                id: comboBox
                model: settings.ipList

//                //如果需要定制下拉列表内容
//                delegate: ItemDelegate {
//                    width: parent.width
//                    height: 40
//                    Text{
//                        anchors.fill: parent
//                        text: "IP" + modelData

//                    }


//                    MouseArea {
//                        anchors.fill: parent
//                        // ...
//                        onClicked: comboBox.popup.close()
//                    }
//                }

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
                text: socketBridge.recPort
            }

            Label {
                text: "QVariant"
            }
            TextField{
                text: settings.value("udp/port")
            }


            Switch{
                Layout.columnSpan: 2
                text: "OK"
                onToggled: console.log(this.checked)
            }

            Button{
                text: "button"
                onClicked: {
                    //settings.value("udp/port") = 222;
                    console.log(settings.value("udp/port"));
                }
            }



            Button{
                text: "ipAddress"
                onClicked: console.log(settings.getIpAddress());
            }

            Button{
                text: "QVariantList"
                onClicked: {
                    settings.ipList.push("127.0.0.2");
                    console.log(settings.ipList);
                }
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
