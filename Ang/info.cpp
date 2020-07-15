#include "info.h"

#include <QtWidgets>

Info::Info(QPushButton *back)
{
    layout = new QGridLayout;
    label = new QLabel(tr("build in progres lol"));

    layout ->addWidget(new QPushButton(tr("guzior")), 1, 1);
    layout -> addWidget(label, 0, 0);
    layout -> addWidget(back, 2, 0);

    resize(550, 370);

    setLayout(layout);

}
