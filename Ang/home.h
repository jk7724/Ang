#ifndef HOME_H
#define HOME_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QGridLayout;
class QTextEdit;
QT_END_NAMESPACE

class Home : public QWidget
{
    Q_OBJECT
public:
    explicit Home(QWidget *parent = nullptr);

signals:
private:

public slots:
};

#endif // HOME_H
