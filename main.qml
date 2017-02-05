import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id:main
    visible: true
    width: 400
    height: 260
    title: qsTr("币众筹采集系统")

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    TextField{
        id:username
        objectName: "username"
        x:100
        y:20
        width: 200
        height: 50
        Text{
            x:-58
            y:10
            text:"账号:"
            font.pixelSize: 16
            color: "white"
        }
    }
    TextField{
        id:password
        objectName: "password"
        x:100
        y:70
        width: 200
        height: 50
        echoMode:TextInput.Password
        Text{
            x:-58
            y:10
            text:"密码:"
            font.pixelSize: 16
            color: "white"
        }
    }
    ProgressBar {
        x:50
        y:160
        width: main.width - 2 * x
        height: 20
        value: 0.5
        indeterminate: false
    }
    Button{
        text:"登录并采集"
        x:(main.width - width) / 2
        y:200
        width: 100
        height:50
        onClicked: {
            httpLib.startCollect();
        }
    }
}
