#include "debitcreditwindow.h"
#include "ui_debitcreditwindow.h"

debitcreditWindow::debitcreditWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::debitcreditWindow)
{
    ui->setupUi(this);
}

debitcreditWindow::~debitcreditWindow()
{
    delete ui;
}
