#ifndef REPETWINDOW_H
#define REPETWINDOW_H

#include <QWidget>
#include "wordbase.h"
#include <memory>
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QPushButton;
class QGridLayout;
class QLabel;
class QVBoxLayout;
class QCheckBox;
class QScrollArea;
class QGroupBox;
class QTextEdit;
class QStackedLayout;
QT_END_NAMESPACE

/*This class provide window interface dedicated to repeat words*/

class ReptWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ReptWindow(QPushButton *back, std::shared_ptr<WordBase> base);

    void infoUPD(); ///update
    QPair<int, int> getWH(){
        return QPair<int, int>(height(), height());
    } //return width and height

public slots:
    void reptStartButt(); //start repeating word(after chose words set to repeat)
    void mainUpdate(); ///update content of lateRep and todayRep
    void backMainButt(); //back to main menu
    void checkButt(); // show if user answer is correct

private:
    std::shared_ptr<WordBase> base_ptr;

    QStackedLayout *stackWidget;
    ///Main Window dedicated to chose which set of words user want to repeat///
    QWidget *mainWindow;
    QGridLayout *mainLayout;
    QGroupBox *lateRep;
    QScrollArea *lateScroll;
    QGroupBox *todayRep;
    QScrollArea *todayScroll;
    QPushButton *backB;
    QPushButton *reptStart;
    QLabel *info;
    QList<QCheckBox*> late;
    QList<QCheckBox*> today;
    ///Child Window dedicate to repeat words (sets chosen earier in main window)///
    QGroupBox *rightAnswerBox;
    QGroupBox *yourAnswerBox;
    QWidget *childWindow;
    QGridLayout *childLayout;
    QPushButton *check;
    QPushButton *backMain;
    QString *downLabelStr;
    QLabel *rightAnswer;
    QLabel *yourAnswer;
    QLabel *engWord;
    QTextEdit *answer;
    QLabel *downLabel_1;
    QLabel *downLabel_2;
    //reppeat staff
    QQueue<int> *repList; ///list of ID sets to repeat
    WordSet *currentSet; //current repeating set
    int currentID;
    int current;
    int end;
    ///function_member///
    bool getChecked(); //add chosen word to Queue repList. Return true if user chose nothing or is nothing to chose
    void makeMainW(); //create main window.
    void makeChild(); //create child window (pop up after click Start! button)
    void setLoad(); //load set to currentSet
    void workDone(); //show measega if you repeat all words
    void nothingToRept(); //show message when nothing left to reppeat or user chose nothing to repeat

};

#endif // REPETWINDOW_H
