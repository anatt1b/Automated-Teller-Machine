#ifndef DEBITCREDITWINDOW_H
#define DEBITCREDITWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class debitcreditWindow;
}
QT_END_NAMESPACE

class debitcreditWindow : public QMainWindow
{
    Q_OBJECT

public:
    debitcreditWindow(QWidget *parent = nullptr);
    ~debitcreditWindow();

private:
    Ui::debitcreditWindow *ui;
};
#endif // DEBITCREDITWINDOW_H
