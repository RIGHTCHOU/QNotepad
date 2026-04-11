// 主窗口头文件

// 1. 头文件保护（防止重复包含）
// 如果没有这个，同一个.h文件被多次#include时会报错
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 2. 包含QMainWindow的头文件
// QMainWindow是Qt提供的“主窗口”基类，自带菜单栏、工具栏、状态栏
#include <QMainWindow>

// 3. 前置声明UI类（Qt的标准写法）
// Ui::MainWindow是从mainwindow.ui文件自动生成的类
// 这里只声明它存在，不包含它的头文件，以加快编译速度
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// 4. 定义我们自己的MainWindow类，继承自QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT// 【关键】必须添加这个宏！
    // 只有加了Q_OBJECT，才能使用Qt的“信号与槽”机制
    // 如果不加，编译会报错

public:

    // 5. 构造函数
    // parent是父窗口指针，默认是nullptr（表示这是一个顶级窗口）
    MainWindow(QWidget *parent = nullptr);

    // 6. 析构函数
    ~MainWindow();

    // 7. 槽函数声明区（slots）
    // 槽函数是Qt中用来响应“信号”的函数（比如“点击按钮”是一个信号，对应的处理函数就是槽函数）
private slots:

    // 【重要】Qt的“自动连接”命名规则
    // 格式：on_控件ID_信号名()
    // 只要槽函数按这个格式命名，Qt会自动把它和对应的控件信号连接起来，不用手动写connect
    // 比如下面这个函数，对应UI文件里ID为actionNew的控件的triggered()信号（即“被点击/触发”）

    void on_actionOpen_triggered();// 对应“打开文件”菜单

    void on_actionCut_triggered();// 对应“剪切”菜单

    void on_actionSave_triggered();// 对应“保存文件”菜单

    void on_actionSave_as_triggered();// 对应“另存为”菜单

    void on_actionCopy_triggered();// 对应“复制”菜单

    void on_actionPaste_triggered();// 对应“粘贴”菜单

    void on_actionRedo_triggered();// 对应“重做”菜单

    void on_actionUndo_triggered();// 对应“撤销”菜单

    void on_actionNew_triggered();// 对应“新建文件”菜单

    void on_actionabout_triggered();// 对应“关于”菜单

    void on_actionFont_triggered();// 对应“设置字体”菜单

    void on_actionColor_triggered();// 对应“设置字体颜色”菜单

    void on_actionText_Background_Color_triggered();// 对应“设置文本背景颜色”菜单

    void on_actionBackground_Color_triggered();// 对应“设置背景颜色”菜单

    void on_actionPrint_triggered();// 对应“打印”菜单

private:
    // 8. 成员变量
    Ui::MainWindow *ui;// 指向UI界面的指针，通过它可以访问UI文件里的所有控件
    QString file_path;// 保存当前打开/编辑的文件的路径（比如"C:/Users/xxx/Documents/test.txt"）
};

// 头文件保护结束
#endif // MAINWINDOW_H
