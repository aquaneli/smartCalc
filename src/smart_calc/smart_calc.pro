QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets \
                                        printsupport
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../src/smart_calc

SOURCES += \
    ../src/s21_opr_stack.c \
    ../src/s21_out_str.c \
    ../src/s21_parcer.c \
    ../src/s21_rev_notation.c \
    ../src/s21_smart_calc.c \
    ../src/smart_calc/graphform.cpp \
    ../src/smart_calc/main.cpp \
    ../src/smart_calc/mainwindow.cpp \
    ../src/smart_calc/qcustomplot.cpp 

HEADERS += \
    ../src/s21_smart_calc.h \
    ../src/smart_calc/graphform.h \
    ../src/smart_calc/mainwindow.h \
    ../src/smart_calc/qcustomplot.h 

FORMS += \
    ../src/smart_calc/graphform.ui \
    ../src/smart_calc/mainwindow.ui 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
