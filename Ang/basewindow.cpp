#include "basewindow.h"
#include <QtWidgets>
#include "wordbase.h"
#include <QTextStream>
#include <memory>

BaseWindow::BaseWindow(QPushButton *back, std::shared_ptr<WordBase> baseW):
    base_ptr(baseW)
{
    layout = new QGridLayout;

    openTxt = new QPushButton(tr("Otwórz plik biblioteki"));
    connect(openTxt, &QPushButton::clicked, this, &BaseWindow::openFile);

    baseString = new QString;
    baseStringUPD();

    base = new QTextEdit(*baseString);
    base->setReadOnly(true);

    //add Widgets to layout
    layout ->addWidget(openTxt, 0, 0);
    layout ->addWidget(back, 1, 0);
    layout ->addWidget(base, 0, 1, 4, 2);

    setLayout(layout);

}

void BaseWindow::openFile()
{
    QDesktopServices::openUrl(QUrl("baza.txt"));
}

void BaseWindow::baseStringUPD()
{
        baseString->clear();
        std::copy_if(base_ptr->getBaseString().begin(), base_ptr->getBaseString().end(), std::back_inserter(*baseString), [](auto c){
        if((c == '*')) return false;
        else if(c=='&') return false;
        else return true;
    });
}
