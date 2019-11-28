import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 1200
    height: 768
    property alias gridWidth: grid.width

    property string ipAddress: "172.16.0.1"

    property bool isUdpOpen: false


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
            Layout.fillWidth: false


            //width: 200
            clip: true




            Label {
                Layout.fillWidth: true
                text: "IP"

            }

            ComboBox {
                id: ipAddressComboBox
                Layout.fillWidth: true
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
                Layout.fillWidth: true
                text: "端口号"
            }
            TextField{
                id: ipPortStr
                Layout.fillWidth: true
                text: settings.value("udp/port")
            }

            Button{
                Layout.columnSpan: 2
                Layout.fillWidth: true
                checkable: true
                text: checked ? "RUNNING" : "START"
                onClicked: {
                    console.log(checked);
                    //绑定信号 执行?or直接在哪里渲染一个开启
                    socketBridge.bindUdp(ipAddressComboBox.currentText,ipPortStr.text)
                }
            }


            Switch{
                Layout.fillWidth: true
                Layout.columnSpan: 2
                text: "OK"
                onToggled: console.log(this.checked)
            }

            Button{
                Layout.fillWidth: true

                text: "button"
                onClicked: {
                    //settings.value("udp/port") = 222;
                    console.log(settings.value("udp/port"));
                }
            }



            Button{
                Layout.fillWidth: true

                text: "ipAddress"
                onClicked: console.log(settings.getIpAddress());
            }

            Button{
                Layout.fillWidth: true

                text: "QVariantList"
                onClicked: {
                    settings.ipList.push("127.0.0.2");
                    console.log(settings.ipList);
                }
            }


        }



        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true

            //需要定义一个图像处理窗口控件 Component

            Rectangle{
                Layout.fillHeight: true
                Layout.fillWidth: true
                height: parent.height/3

                color: "#CCC"
                Image{
                    width: parent.width
                    height: width/188*120
                    source: "file:///P:/qt/smartcar/GodHelper2.0/DataBridge/Images/test--2110444809.bmp"
                    Text{
                        width: parent.width
                        height: parent.width
                        anchors.fill: parent
                        text: "Picture"
                        color: "#FFF"
                    }
                    Rectangle{
                        width: parent.width
                        height: 40
                        color: "#55FFFFFF"
                        anchors.bottom: parent.bottom
                    }
                }
            }

            Rectangle{
                Layout.fillWidth: true
                Layout.fillHeight: true
                height: parent.height/3

                color: "#DDD"
                Text {
                    width: parent.width
                    text: qsTr("Monitor")
                }
            }
        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "#CCC"

            TextArea{
                anchors.fill: parent
                text: "MessageData"
            }

        }
    }

}
