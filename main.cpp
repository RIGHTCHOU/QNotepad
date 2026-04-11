// 程序入口

// 1. 包含主窗口类的头文件
#include "mainwindow.h"

// 2. 包含QApplication头文件
// QApplication是Qt应用程序的核心类，负责管理应用的事件循环（比如鼠标点击、键盘输入）
#include <QApplication>

int main(int argc, char *argv[])
{
    // 3. 创建QApplication对象
    // argc和argv是命令行参数，Qt需要用它们来处理一些命令行选项（比如启动时的样式）
    QApplication a(argc, argv);

    // 4. 创建主窗口对象
    // MainWindow是我们自己定义的类，继承自QMainWindow
    MainWindow w;

    // 5. 设置窗口标题（可选，也可以在MainWindow构造函数里设置）
    w.setWindowTitle("QNotepad");

    // 6. 显示窗口
    // 注意：Qt的窗口创建后默认是隐藏的，必须调用show()才会显示
    w.show();

    // 7. 进入应用程序的事件循环
    // a.exec()会让程序一直运行，直到用户关闭窗口
    // 它的作用是“卡住”程序，不断监听用户的操作（点击、打字等），并分发给对应的处理函数
    return a.exec();
}
