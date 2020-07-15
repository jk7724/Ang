#include "repetwindow.h"
#include <QtWidgets>
#include <QStackedLayout>

ReptWindow::ReptWindow(QPushButton *back, std::shared_ptr<WordBase> base):
    base_ptr(base)
{

    repList = new QQueue<int>;

    mainWindow = new QWidget;
    childWindow = new QWidget;
    stackWidget = new QStackedLayout;
    mainLayout = new QGridLayout;
    QFont font("cambria", 12);
    info = new QLabel(tr("Zaznacz zestawy które chcesz powtórzyć i naciśnij 'Start!'"));
    info ->setAlignment(Qt::AlignCenter);
    info->setFont(font);

    backB=back;
    reptStart = new QPushButton(tr("Start!"));
    connect(reptStart, &QPushButton::clicked, this, &ReptWindow::reptStartButt);
    lateRep = new QGroupBox(tr("Przegapione powtórki"));
    lateRep->setMaximumSize(500, 100);

    todayRep = new QGroupBox(tr("Dzisiejsze powtórki"));
    lateScroll = new QScrollArea;
    todayScroll = new QScrollArea;

    mainUpdate();
    makeMainW();
    makeChild();

    mainWindow->setLayout(mainLayout);
    childWindow->setLayout(childLayout);
    stackWidget->addWidget(mainWindow);
    stackWidget->addWidget(childWindow);

    setLayout(stackWidget);

}
void ReptWindow::reptStartButt()
{

    if(getChecked()) return; //check if chose any set. If no, return

    setLoad();
    stackWidget->setCurrentIndex(1); //open child window

}
void ReptWindow::backMainButt()
{
    //show message if user decide to leave repeatition before finish it.
    QMessageBox msgBox;
    msgBox.setText("Pozostalo " + QString::number(end-current) + " słówek do powtórzenia. Wyjscie spowoduje utratę postępów" );
    QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);

    msgBox.exec(); // create dialog windows.

    if (msgBox.clickedButton() == okButton) {
        getChecked();
        stackWidget->setCurrentIndex(0);
        backB->animateClick();
    } else if (msgBox.clickedButton() == cancelButton) {
        return;
    }
}
void ReptWindow::checkButt()
{
    if(answer->toPlainText().isEmpty()) return;

    rightAnswer->setText(currentSet->getEngPln(current));
    yourAnswer->setText(QString("Twoja odpowiedź: ")+answer->toPlainText());
    answer->clear();
    engWord->setText(currentSet->getPln(current+1));
    current++;
    downLabel_2->setText("Pozostało: " + QString::number(end-current) +" słówek");
    if(current == end)
    {
        setLoad();
        base_ptr->erSetfTer(currentID);
        getChecked();
        mainUpdate();
        makeMainW();
    }
}
void ReptWindow::mainUpdate()
{
    //get information about set, that user shoud repeat
    QVector<int> todayR = base_ptr->todaySet();
    QSet<int> lateR = base_ptr->lateSet();

    if(late.empty() != true)
    {
        late.clear();
    }
    if(today.empty()!= true)
    {
        today.clear();
    }
    delete lateRep;
    delete todayRep;
    lateRep = new QGroupBox(tr("Powtórki spóźnione"));
    todayRep = new QGroupBox(tr("Powtórki na dzisiaj"));
    auto lateLayout = new QVBoxLayout;
    auto todayLayout = new QVBoxLayout;

    ///create QCheckBox
    if(todayR.empty() != true)
    {
        std::for_each(todayR.begin(), todayR.end(), [this, &todayLayout](int i){
            this->today.push_back(new QCheckBox(QString::number(i)));
            today.back()->setChecked(true);
            todayLayout -> addWidget(today.back());
        });
    }
    if(lateR.empty() != true)
    {
        std::for_each(lateR.begin(), lateR.end(), [this, &lateLayout](int i){
            this->late.push_back(new QCheckBox(QString::number(i)));
            lateLayout ->addWidget(late.back());
        });
    }
    lateRep->setLayout(lateLayout);
    todayRep->setLayout(todayLayout);
}
bool ReptWindow::getChecked()
{
    repList->clear();

    if(today.isEmpty() && late.isEmpty())
    {
        nothingToRept();
        return true;
    }
    else
    {
        if(!(today.isEmpty()))
        {
            std::for_each(today.begin(), today.end(), [this](auto i)
            {
                if(i->QAbstractButton::isChecked())
                {
                    this->repList->enqueue(i->text().toInt());
                }
            });
        }
        if(!(late.isEmpty()))
        {
            std::for_each(late.begin(), late.end(), [this](auto i)
            {
                if(i->QAbstractButton::isChecked())
                {
                    this->repList->enqueue(i->text().toInt());
                }
            });
        }
        if(repList->isEmpty())
        {
            nothingToRept();
            return true;
        }

    }
    return false;
}

void ReptWindow::makeMainW()
{
    mainLayout ->addWidget(info, 0, 0);
    mainLayout ->addWidget(lateRep, 1, 0);
    mainLayout ->addWidget(todayRep, 2, 0);
    mainLayout ->addWidget(reptStart, 3, 0);
    mainLayout ->addWidget(backB, 4, 0);

}

void ReptWindow::makeChild()
{
    childLayout = new QGridLayout;

    QFont font("cambria", 12);

    rightAnswerBox = new QGroupBox("Prawidłowa odpowiedź");
    rightAnswer= new QLabel(tr("..............."));
    rightAnswer->setFont(font);
    rightAnswer->setAlignment(Qt::AlignCenter);
    yourAnswer = new QLabel(tr("..............."));
    yourAnswer->setAlignment(Qt::AlignCenter);
    yourAnswer->setFont(font);
    engWord = new QLabel;
    engWord ->setAlignment(Qt::AlignCenter);
    engWord->setFont(font);

    answer = new QTextEdit;
    answer -> setFixedSize(170, 25);
    backMain = new QPushButton(tr("Powrót"));
    connect(backMain, &QPushButton::clicked, this, &ReptWindow::backMainButt);
    downLabel_1 = new QLabel("Zestaw 4");
    downLabel_2 = new QLabel("Pozostalo ... slowek");
    downLabelStr = new QString;
    check = new QPushButton(tr("Sprawdz!"));
    connect(check, &QPushButton::clicked, this, &ReptWindow::checkButt);
    QLabel *filer = new QLabel;
    QLabel *filer2 = new QLabel;


    childLayout ->addWidget(filer, 0, 0, 3, 1);
    childLayout -> addWidget(engWord, 1, 0);
    childLayout -> addWidget(answer, 1, 1);
    childLayout -> addWidget(check, 1, 2);

    childLayout -> addWidget(rightAnswer, 2, 0, 1, 3);
    childLayout -> addWidget(yourAnswer, 3, 0, 1, 3);

    childLayout -> addWidget(backMain, 4, 0);
    childLayout -> addWidget(downLabel_1, 4, 1);
    childLayout -> addWidget(downLabel_2, 4, 2);
}

void ReptWindow::setLoad()
{
    if(repList->size() == 0 )
    {
        currentSet = nullptr;
        workDone(); //if nothing left to repeat, show message
        return;
    }
    currentID = repList->dequeue();
    currentSet = base_ptr->getSet(currentID);
    current = 0;
    end = currentSet->getSize();
    engWord->setText(currentSet->getPln(0));
    downLabel_1->setText("Zestaw nr " + QString::number(currentID));
    downLabel_2->setText("Pozostało: " + QString::number(end) + " słówek");

}

void ReptWindow::workDone()
{
    QMessageBox msgBox;
    msgBox.setText("Wszystko powtórzone, dobra robota!");
    QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == okButton) {
        stackWidget->setCurrentIndex(0);
        backB->animateClick();
    }
}

void ReptWindow::nothingToRept()
{
    QMessageBox msgBox;
    msgBox.setText("Nie wybrano zestawów do powtórzenia/brak zestawów do powtórzenia.");
    msgBox.setStandardButtons(QMessageBox::Ok);

    msgBox.exec();

}
