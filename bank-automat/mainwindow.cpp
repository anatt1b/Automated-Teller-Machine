#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    connect(ui->btnLogin, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    });

    connect(ui->pinInput, &QLineEdit::returnPressed, this, [this]() {
        ui->btnLogin->click();
    });

    connect(ui->btnBalance, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageBalance);
    });

    connect(ui->btnDeposit, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageDeposit);
    });

    connect(ui->btnWithdrawn, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageWithdraw);
    });

    connect(ui->btnTransactions, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageTransactions);
    });

    connect(ui->btnBackBalance, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    });

    connect(ui->btnBackDeposit, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    });

    connect(ui->btnBackWithdrawn, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    });

    connect(ui->btnBackTransactions, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    });

    connect(ui->btnLogout, &QPushButton::clicked, this, [this]() {
        ui->pinInput->clear();
        ui->stackedWidget->setCurrentWidget(ui->pageLogin);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
