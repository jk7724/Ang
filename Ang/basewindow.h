#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include "wordbase.h"
#include <QScopedPointer>
#include <memory>


QT_BEGIN_NAMESPACE
class QPushButton;
class QGridLayout;
class QTextEdit;
class QLabel;
QT_END_NAMESPACE

/*This class provide window that display Words library*/

class BaseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWindow(QPushButton *back, std::shared_ptr<WordBase> baseW);

signals:

public slots:
    void openFile(); //open Words library .txt file
    void baseStringUPD(); //update displaying Word library
private:
    std::shared_ptr<WordBase> base_ptr; //pointer to main word library

    QGridLayout *layout;
    QString *baseString;
    QPushButton *loadButton;
    QPushButton *openTxt;
    QTextEdit *base;
};

#endif // BASEWINDOW_H
