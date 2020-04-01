import QtQuick 2.12
import QtQuick.Window 2.12


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    PanelMeter
    {
         objectName: "TempMeter"
         x:10
         y:10
         width: 100
         height: 100
    }
    PanelMeter
    {
        objectName: "TiltMeter"
        x:120
        y:10
        width: 100
        height: 100

    }

}
