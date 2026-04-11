# 1. 添加Qt核心模块
# core: 核心非GUI功能（QString, QFile等）
# gui: GUI基础模块
# printsupport: 打印支持模块（因为项目里有打印功能）
# Git
QT       += core gui printsupport

# 2. 兼容Qt5/Qt6：如果Qt主版本大于4（即Qt5及以上），额外添加widgets模块
# Qt5把GUI控件从gui模块独立到了widgets模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 3. 编译配置：使用C++17标准
CONFIG += c++17

# 4. 禁用过时的API（可选，让代码更规范）
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 5. 源文件列表（所有.cpp文件）
SOURCES += \
    main.cpp \
    mainwindow.cpp

# 6. 头文件列表（所有.h文件）
HEADERS += \
    mainwindow.h

# 7. 界面文件列表（所有.ui文件）
# Qt会通过UIC工具把.ui文件转换成C++头文件（ui_mainwindow.h）
FORMS += \
    mainwindow.ui

# 8. Windows特有的程序图标
# Add the icon line below this:
RC_ICONS = myappico.ico

# 9. 安装规则（默认生成的）
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 10. Qt资源文件（存放图片、图标等资源）
RESOURCES += \
    resource.qrc
