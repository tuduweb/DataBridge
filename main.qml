import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 800
    height: 680
    property alias gridWidth: grid.width
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

            TextInput{
                text: "333"
            }

            Label {
                text: "IP"
            }
            TextInput{
                text: "333"
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
