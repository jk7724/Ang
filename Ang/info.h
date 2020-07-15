#ifndef INFO_H
#define INFO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QGridLayout;
QT_END_NAMESPACE

class Info: public QWidget
{
    Q_OBJECT
public:
    explicit Info(QPushButton *back = nullptr);


private:
    QGridLayout *layout;
    QLabel *label;
    QPushButton *backButton;

};

#endif // INFO_H
