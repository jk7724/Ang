#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "wordbase.h"
#include "basewindow.h"
#include "addword.h"
#include "repetwindow.h"

#include <memory>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QTextEdit;
class QGridLayout;
QT_END_NAMESPACE

/* Main window of the program */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
public slots:
    void changeWindow(); //load chosen window
    void backHome(); //back to main window

private:
    std::shared_ptr<WordBase> wordB;
    QWidget *home;
    BaseWindow *baseWindow;
    AddWord *addWordWindow;
    ReptWindow *reptWindow;

    QPushButton *addButton;
    QPushButton *baseButton;
    QPushButton *exitButton;
    QPushButton *repeatButton;

    QPushButton *backBase;
    QPushButton *backInfo;
    QPushButton *backCal;
    QPushButton *backAdd;
    QPushButton *backRepeat;

    QGridLayout *mainLayout;

};

#endif // MAINWINDOW_H
