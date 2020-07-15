#ifndef ADDWORD_H
#define ADDWORD_H

#include <QWidget>
#include "wordbase.h"
#include <QScopedPointer>
#include <memory>

QT_BEGIN_NAMESPACE
class QPushButton;
class QGridLayout;
class QTextEdit;
class QLabel;
class QRadioButton;
class QVBoxLayout;
QT_END_NAMESPACE

/*This class provide window interface dedicated to adding a new sets of words*/

class AddWord : public QWidget
{
    Q_OBJECT
public:
    explicit AddWord(QPushButton *back, std::shared_ptr<WordBase> base);
    ~AddWord(){saveTemp();}
public slots:
    void clearButt(); //clear temporary word set
    void saveButt(); //add temporary word set to Word Library and generate repetition
    void addButt(); //pop up window dedicated to adding new words
    void otherAddButt(); //add new word to temporary set

private:
    WordSet tempSet; //temporary word set
    std::shared_ptr<WordBase> base_ptr; //pointer to Word Library
    QGridLayout *layout;

    QPushButton *addButton;
    QPushButton *clearButton;
    QPushButton *saveButton;

    QTextEdit *words;

    QWidget *addWindow;
    QGridLayout *addLayout;
    QLabel *message;
    QTextEdit *write;
    QTextEdit *wordEng;
    QTextEdit *wordPln;
    QPushButton *close;
    QPushButton *add;

    /////
    void makeAddWindow(); //create pop up window dedicated to add new polish-engilish word
    void saveTemp(); //save temporary set to file
    void loadTemp(); //load temporary set from file
    void setWords(); //write temporary words( in QTextedit *write)
};


#endif // ADDWORD_H

