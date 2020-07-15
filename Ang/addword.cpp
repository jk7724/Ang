#include "addword.h"
#include "wordbase.h"
#include <QtWidgets>

AddWord::AddWord(QPushButton *back, std::shared_ptr<WordBase> base):
    base_ptr(base)

{
    loadTemp();
    makeAddWindow();

    layout = new QGridLayout;

    //set buttons
    addButton = new QPushButton(tr("Dodaj slowo"));
    connect(addButton, &QPushButton::clicked, this, &AddWord::addButt);
    clearButton = new QPushButton(tr("Wyczysc"));
    connect(clearButton, &QPushButton::clicked, this, &AddWord::clearButt);
    saveButton = new QPushButton(tr("Dodaj do powtorek"));
    connect(saveButton, &QPushButton::clicked, this, &AddWord::saveButt);

    words = new QTextEdit("Hiszpanska inkwizycja");
    words->setReadOnly(true);
    setWords();

    //add Widget to layout
    layout ->addWidget(addButton,0,0);
    layout ->addWidget(clearButton, 1, 0);

    layout ->addWidget(saveButton, 4, 1, 1, 2);
    layout ->addWidget(back, 4, 0);
    layout ->addWidget(words, 0, 1, 4, 2);

    setLayout(layout);


}

void AddWord::clearButt()
{
    tempSet.clear();
    setWords();
}

void AddWord::saveButt()
{
    if(tempSet.getSize() == 0) return;
    else
    {
        int ID = base_ptr->addNewSet(tempSet); //add temporary set to Word Library
        base_ptr-> addTerm(ID); //generate term of repetition
        base_ptr->BaseStrUpdate(tempSet); //update base Window
        base_ptr->saveBase(); //save updated base file (Word Library source file)
        clearButt();
    }

}

void AddWord::addButt()
{

    addWindow->show();

}

void AddWord::otherAddButt()
{
    if(wordPln->toPlainText().isEmpty() || wordEng->toPlainText().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Jedno z pól jest puste. Uzupełnij pola by dodać słowo.");
        msgBox.setStandardButtons(QMessageBox::Ok);

        msgBox.exec();

    }
    else
    {
        tempSet.addWord(wordPln->toPlainText(), wordEng->toPlainText()); //add new word to temporary set
        wordPln->clear();
        wordEng->clear();
        setWords();

    }

}
void AddWord::makeAddWindow()
{
    addWindow = new QWidget();
    addWindow ->resize(100, 50);
    addWindow ->move(550, 500);
    addLayout = new  QGridLayout();

    message = new QLabel("Wpisz slowo wedlug wzoru: polskie - angielskie i kliknij 'Dodaj słowo'.");

    write = new QTextEdit();
    write->setReadOnly(false);

    wordEng = new QTextEdit();
    wordEng->setReadOnly(false);
    wordPln= new QTextEdit();
    wordPln->setReadOnly(false);

    close = new QPushButton(tr("Zamknij"));
    connect(close, &QPushButton::clicked, addWindow, &QWidget::close);
    add = new QPushButton(tr("Dodaj slowo"));
    connect(add, &QPushButton::clicked, this, &AddWord::otherAddButt);

    //add Widget to layout
    addLayout->addWidget(message, 0, 0, 1, 2);
    addLayout ->addWidget(wordPln, 1, 0, 1, 1);
    addLayout ->addWidget(wordEng, 1, 1, 1, 1);
    addLayout ->addWidget(add, 2, 0, 1, 2);
    addLayout ->addWidget(close, 3, 0, 1, 2);

    addWindow ->setLayout(addLayout);

}

void AddWord::saveTemp()
{
    QFile file("temp.txt");
    if(!file.open(QFile::WriteOnly| QFile::Text))
    {
        qDebug()<<file.errorString();
        qDebug()<<"nie moge otworzyc pliku";
        return;
    }

    QTextStream stream(&file);

    if(tempSet.getSize()==0) return;
    stream << tempSet.getWordSetString();
    stream.flush();

    file.close();
}

void AddWord::loadTemp()
{
    QFile file("temp.txt");
    if(!file.open(QFile::ReadOnly| QFile::Text))
    {
        qDebug()<<file.errorString();
        qDebug()<<"nie moge otworzyc pliku";
        return;
    }
    QTextStream stream(&file);

    QString pln, eng, blip;
    while(!stream.atEnd())
    {
        stream >> pln >> blip >> eng >> blip;
        tempSet.addWord(pln, eng);
        stream.skipWhiteSpace();
    }
    file.close();

}

void AddWord::setWords()
{
    words->setText(tempSet.getWordSetString());
}
