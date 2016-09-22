import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

ApplicationWindow {
    id: main
    visible: true
    width: 400
    height: 600

    Text{
        anchors.centerIn: parent
        text: "Hello World"
    }
    Image{
        anchors.centerIn: parent
        source:"http://news.tsinghua.edu.cn/publish/thunews/9660/20160910173951579107723/1473500679542.jpg";
    }

}
