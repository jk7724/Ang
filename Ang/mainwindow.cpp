#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wordbase.h"
#include <QtWidgets>
#include <memory>


MainWindow::MainWindow()
{
    wordB = std::make_shared<WordBase>(tr("baza.txt")); //definition of Word Library

    //main windows
    home = new QWidget();

    //set back to main window buttons
    backBase = new QPushButton(tr("Powrót"));
    connect(backBase, &QPushButton::clicked, this, &MainWindow::backHome);
    backInfo = new QPushButton(tr("Powrót"));
    connect(backInfo, &QPushButton::clicked, this, &MainWindow::backHome);
    backAdd = new QPushButton(tr("Powrót"));
    connect(backAdd, &QPushButton::clicked, this, &MainWindow::backHome);
    backCal = new QPushButton(tr("Powrót"));
    connect(backCal, &QPushButton::clicked, this, &MainWindow::backHome);
    backRepeat = new QPushButton(tr("Powrót"));
    connect(backRepeat, &QPushButton::clicked, this, &MainWindow::backHome);

    //definition of other window
    baseWindow = new BaseWindow(backBase, wordB);
    addWordWindow = new AddWord(backAdd, wordB);
    reptWindow = new ReptWindow(backRepeat, wordB);

    //definition of main window widgets
    mainLayout = new QGridLayout();
    addButton = new QPushButton(tr("Dodaj słówka"));
    addButton->setProperty("index", 1);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::changeWindow);

    baseButton = new QPushButton(tr("Słownik"));
    baseButton->setProperty("index", 3);
    connect(baseButton, &QPushButton::clicked, this, &MainWindow::changeWindow);

    repeatButton = new QPushButton(tr("Zacznij powtórkę"));
    repeatButton->setProperty("index", 5);
    connect(repeatButton, &QPushButton::clicked, this, &MainWindow::changeWindow);

    exitButton = new QPushButton(tr("Wyjście"));
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);

    mainLayout ->addWidget(addButton, 0, 0);
    mainLayout ->addWidget(repeatButton, 1, 0);
    mainLayout ->addWidget(baseButton, 2, 0);
    mainLayout ->addWidget(exitButton, 3, 0);

    home -> setLayout(mainLayout);

    setWindowTitle(tr("Angielski"));
    resize(500, 270);
    setCentralWidget(home);

}

void MainWindow::changeWindow()
{
    centralWidget()->setParent(nullptr); //to set new Central Widget need first setParent to nullptr
    QPushButton *temp = qobject_cast<QPushButton*>(sender());
    int index = temp->property("index").toInt();
    switch(index)
    {

        case 1:
        setCentralWidget(addWordWindow);
        break;
        case 2:
        break;
        case 3:
        baseWindow->baseStringUPD();
        setCentralWidget(baseWindow);
        break;
        case 4:
        break;
        case 5:
        auto d = reptWindow->getWH();
        setFixedSize(d.first, d.second);
        setCentralWidget(reptWindow);
        break;

    }

}

void MainWindow::backHome()
{
    centralWidget()->setParent(nullptr);
    setCentralWidget(home);
    setFixedSize(500, 270);
}

