// 主窗口实现文件

#include "mainwindow.h"
#include "ui_mainwindow.h"
// 【关键】包含UI文件生成的头文件
// 这个文件是Qt在编译时自动从mainwindow.ui生成的，不用手动写
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPrinter>
#include <QPrintDialog>

// 构造函数：窗口初始化
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)// 调用父类QMainWindow的构造函数
    , ui(new Ui::MainWindow) // 创建UI对象
{
    // 1. 把UI文件里设计的界面“安装”到当前窗口
    // 这一步会把菜单栏、工具栏、文本框等所有控件都创建出来
    ui->setupUi(this);

    // 2. 设置中心部件（Central Widget）
    // QMainWindow的结构是：菜单栏在顶，工具栏在边，状态栏在底，中间空着
    // setCentralWidget就是把中间的区域填满指定的控件
    // 这里我们把文本编辑区（textEdit）设为中心部件，让它铺满整个窗口
    this->setCentralWidget(ui->textEdit);//help to remove space from side

    // 3. 【进阶】实时字符计数功能（手动连接信号与槽）
    // 这里用了C++11的Lambda表达式作为槽函数
    // 逻辑：当textEdit的内容发生变化（textChanged信号）时，执行Lambda里的代码
    // Assuming QTextEdit named 'textEdit' and a QStatusBar named 'statusBar'
    connect(ui->textEdit, &QTextEdit::textChanged, this, [=] {
        // 获取文本框里的纯文本，计算长度
        int charCount = ui->textEdit->toPlainText().length();
        // 在状态栏显示字符数，显示2000毫秒（2秒）
        ui->statusbar->showMessage(QString("Character count: %1").arg(charCount), 2000);
    });

}

// 析构函数：清理内存
MainWindow::~MainWindow()
{
    delete ui;// 释放UI对象
}

// 文件操作

// 对应“新建文件”菜单
void MainWindow::on_actionNew_triggered()
{
    // 逻辑很简单：清空文本编辑区，并清空当前文件路径
    file_path = "";// 清空保存的路径，这样下次“保存”时会相当于“另存为”
    ui->textEdit->setText("");// setText传入空字符串，即清空
}

// 对应“打开文件”菜单
void MainWindow::on_actionOpen_triggered()
{
    // 1. 弹出“打开文件”对话框，让用户选择文件
    // 参数：父窗口指针、对话框标题、默认打开路径（空表示当前目录）、文件过滤器
    // 返回值：用户选择的文件的完整路径（如果用户点取消，返回空字符串）
    QString file_name = QFileDialog::getOpenFileName(this,"open the file");

    // 2. 创建QFile对象，关联到这个文件
    QFile file(file_name);

    // 3. 把选择的路径保存到成员变量里（方便后续保存）
    file_path = file_name;

    // 4. 尝试打开文件
    // OpenMode：ReadOnly（只读） | Text（文本模式，自动处理换行符）
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        // 如果打开失败（比如文件被占用、权限不足），弹出警告框
        QMessageBox::warning(this,"..","file not open");
        return;// 直接返回，不执行后面的代码
    }

    // 5. 读取文件内容
    QTextStream in(&file);// 创建文本流，关联到文件
    QString text = in.readAll();// 读取文件的全部内容到QString

    // 6. 把读取到的内容显示在文本编辑区
    ui->textEdit->setText(text);

    // 7. 关闭文件（好习惯，虽然QFile析构时会自动关，但手动关更安全）
    file.close();
}

// 对应“保存文件”菜单
void MainWindow::on_actionSave_triggered()
{
    // 1. 检查是否有当前文件路径
    // 如果file_path为空，说明是新建的文件还没保存过，此时应该调用“另存为”
    if (file_path.isEmpty()) {
        on_actionSave_as_triggered(); // 直接调用另存为的槽函数
        return;
    }

    // 2. 创建QFile对象，关联文件
    QFile file(file_path);

    // 3. 尝试以“只写”模式打开文件
    // WriteOnly：写入模式（会覆盖原有内容）
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }

    // 4. 写入内容
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();// 获取文本框里的纯文本
    out << text;// 把文本写入文件（类似cout的用法）

    // 5. 刷新缓冲区并关闭文件
    file.flush();// 确保数据真正写入磁盘，而不是留在内存缓冲区
    file.close();
}

// 对应“另存为”菜单
void MainWindow::on_actionSave_as_triggered()
{
    // 参数和getOpenFileName类似
    QString file_name = QFileDialog::getSaveFileName(this,"open the file");
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

// 对应“剪切”菜单
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


// 对应“复制”菜单
void MainWindow::on_actionCopy_triggered()
{
     ui->textEdit->copy();
}

// 对应“粘贴”菜单
void MainWindow::on_actionPaste_triggered()
{
     ui->textEdit->paste();
}

// 对应“重做”菜单
void MainWindow::on_actionRedo_triggered()
{
     ui->textEdit->redo();
}

// 对应“撤销”菜单
void MainWindow::on_actionUndo_triggered()
{
     ui->textEdit->undo();
}

// 对应“关于”菜单
void MainWindow::on_actionabout_triggered()
{
    QString about_text;
    about_text = "Author : ZZH\n";
    about_text += "Date : 06/07/2025\n";
    about_text += "(C) QNotepad (R)";

    QMessageBox::about(this,"About QNotepad",about_text);
}

// 对应“设置字体”菜单
void MainWindow::on_actionFont_triggered()
{
    bool ok;// 用于接收用户是否点击了“确定”

    // 1. 弹出字体选择对话框
    // 参数：初始字体（这里用textEdit的当前字体）、ok指针、父窗口
    QFont font = QFontDialog::getFont(&ok,this);

    // 2. 如果用户点击了确定，就把textEdit的字体设为选择的字体
    if(ok){
        ui->textEdit->setFont(font);
    }else{
        return;
    }
}

// 对应“设置字体颜色”菜单
void MainWindow::on_actionColor_triggered()
{
    // 1. 弹出颜色选择对话框
    // 参数：初始颜色（这里用textEdit的当前字本颜色）、父窗口
    QColor color = QColorDialog::getColor(Qt::white,this,"choose color");

     // 2. 如果颜色有效（用户没点取消），设置字本颜色
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }else{
        return;
    }
}

// 对应“设置文本背景颜色”菜单
void MainWindow::on_actionText_Background_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}

// 对应“设置背景颜色”菜单
void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()){
        ui->textEdit->setPalette(QPalette(color));
    }
}

// 对应“打印”菜单
void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;// 创建打印机对象
    printer.setPrinterName("Micosoft printer");// 设置打印机姓名
    // 1. 弹出打印对话框
    QPrintDialog dialog(&printer,this);

    // 2. 如果用户点击了取消，直接返回
    if(dialog.exec()==QDialog::Rejected) return;

    // 3. 调用textEdit的print方法进行打印
    ui->textEdit->print(&printer);
}

