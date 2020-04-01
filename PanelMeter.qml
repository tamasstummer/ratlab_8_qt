import QtQuick 2.0

Item {
    id: root
    property real meterValue : 0
    property bool centerMode: false
    property real ratio: 1
    property bool alarm: false

    function valueChanged(value)
    {
        meterValue = value;
    }

    function alarmStateChanged(state){
        if(state == 1)
        {
            alarm = true;
        }
        else
        {
            alarm = false;
        }
    }


    onRatioChanged:
    {
        if(ratio == 0)
        {
            ratio = 1
        }
    }

    onMeterValueChanged:
    {

        //0-180
        if(centerMode == false)
        {
            if(meterValue * ratio >= 180){
                meterValue = 180 / ratio;
            }
            else if(meterValue <= 0){
                meterValue = 0;
            }

            needle.rotation = meterValue * ratio - 90;
        }
        else {
            if(meterValue * ratio >= 90){
                meterValue = 90 / ratio;
            }
            else if(meterValue * ratio <= -90){
                meterValue = -90 / ratio;
            }
            needle.rotation = meterValue * ratio;
        }

        canvas.requestPaint();
    }

    width: 300; height: 300

    Timer {
        interval: 500;
        running: alarm;
        repeat: true
        onTriggered:{

            if (canvas.alarmOpacity == 0.7)
            {
                canvas.alarmOpacity = 1
            }
            else
            {
                canvas.alarmOpacity = 0.7
            }

            canvas.requestPaint();
        }
    }

    Rectangle {
        id: meter
        color: "#00000000"
        anchors.fill: parent

        Canvas {
            property real alarmOpacity : 0.7

            id: canvas
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();

                var centreX = width / 2;
                var centreY = height / 2;

                var offset = Math.PI;

                if(root.centerMode == true){
                    offset = Math.PI * 1.5;
                }

                var from = offset;
                var to = offset + Math.PI * 2 * root.meterValue * root.ratio / 360;

                if(root.meterValue * ratio < 0){
                    from = offset + Math.PI * 2 * root.meterValue * root.ratio / 360;
                    to = offset;
                }

                ctx.beginPath();
                ctx.strokeStyle = "white";

                var opacity = 0.4;
                if(root.alarm == true){
                    opacity = alarmOpacity;
                }

                if(root.centerMode == true)
                {
                    ctx.fillStyle = Qt.rgba(Math.abs(root.meterValue * root.ratio / 90), 1 - Math.abs(root.meterValue * root.ratio / 90), 0, opacity);
                }
                else
                {
                    ctx.fillStyle = Qt.rgba(Math.abs(root.meterValue * root.ratio / 180), 1 - Math.abs(root.meterValue * root.ratio / 180), 0, opacity);
                }

                ctx.moveTo(centreX, centreY);

                ctx.arc(centreX, centreY, width / 2.5, from, to, false);

                ctx.lineTo(centreX, centreY);
                ctx.fill();

                ctx.beginPath();
                if(root.centerMode == true)
                {
                    ctx.strokeStyle = Qt.rgba(Math.abs(root.meterValue * root.ratio / 90), 1 - Math.abs(root.meterValue * root.ratio / 90), 0.1, 1);
                }
                else
                {
                    ctx.strokeStyle = Qt.rgba(Math.abs(root.meterValue * root.ratio / 180), 1 - Math.abs(root.meterValue * root.ratio / 180), 0.1, 1);
                }
                ctx.arc(centreX, centreY, width/2.3, from, to, false);
                ctx.lineWidth = 30
                ctx.stroke();
            }
        }

        Text {
            text: meterValue
            font.bold: true
            font.family: "Tahoma"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 20
            y: 220
            anchors.horizontalCenter: canvas.horizontalCenter
        }

        Image {
            id: needle
            x: 162
            y: 53
            width: 35
            height: 300
            transformOrigin: Item.Center
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            source: "needle"
            Behavior on rotation {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
}
