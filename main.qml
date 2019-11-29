import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: app
    visible: true
    width: 1280
    height: 720
    //property alias gridWidth: grid.width

    property string ipAddress: "172.16.0.1"

    property bool isUdpOpen: false
    signal bindUdp(string ip,int port)


    title: qsTr("DataBridge")



    //本工具是为了写数据接口

//    header: ToolBar{

//    }

    RowLayout{
//        width: parent.width
//        height: parent.height
        clip: false
        anchors.fill: parent

        Layout.leftMargin: 5



        ColumnLayout{
            Layout.maximumWidth: 250
            Layout.fillWidth: true
            Layout.fillHeight: true



            //Layout.fillWidth: true

            Rectangle{
                id: socketWrap
                Layout.maximumHeight: 150
                Layout.fillHeight: true
                Layout.fillWidth: true

                GridLayout {

                    id: socketWrapLayout
                    columns: 2
                    anchors.fill: parent


                    //Layout.fillWidth: true


                    //width: 200
                    clip: true




                    Label {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        text: "IP"

                    }

                    ComboBox {
                        id: ipAddressComboBox
                        Layout.fillWidth: true
                        Layout.fillHeight: true

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
                        Layout.fillHeight: true

                        text: "端口号"
                    }
                    TextField{
                        id: ipPortStr
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        text: settings.value("udp/port")
                    }

                    Button{


                        Layout.columnSpan: 2
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        checkable: true
                        text: checked ? "RUNNING" : "START"
                        onClicked: {
                            console.log(checked);
                            //绑定信号 执行?or直接在哪里渲染一个开启
                            //socketBridge.bindUdp(ipAddressComboBox.currentText,ipPortStr.text)
                            bindUdp(ipAddressComboBox.currentText,ipPortStr.text)
                            //socketWrap.color = "#ccc"
                        }
                        Component.onCompleted:{
                            bindUdp.connect(dataCenter.bindUdpSlot);
                        }
                    }


//                    Component.onCompleted: {
//                        console.log(socketWrapLayout.children)
//                        for(var i in socketWrapLayout.children)
//                            console.log(socketWrapLayout.children[i].anchors.leftMarin = 5)
//                    }








                }

            }

            Item{
                Layout.fillWidth: true
                Layout.fillHeight: true

                RowLayout{
                    anchors.fill: parent

                    Label{
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: qsTr("RateMonitor")
                        font.pixelSize: 18
                        font.family: "Microsoft YaHei"
                        //Layout.margins: 2
                        //Layout.leftMargin: 5
                    }

                    Text{
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: qsTr("100kb/s")
                    }
                }

            }

            Switch{
                Layout.fillWidth: true
                text: "OK"
                onToggled: console.log(this.checked)
            }




        }


        ColumnLayout{
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

        ColumnLayout{

            Layout.fillHeight: true
            Layout.fillWidth: true

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

}
