#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    manager = new QNetworkAccessManager(this);

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
        webToken.clear();
        ui->cardInput->clear();
        ui->pinInput->clear();
        ui->stackedWidget->setCurrentWidget(ui->pageLogin);
    });
}

void MainWindow::on_btnLogin_clicked()
{
    // luetaan kentät
    QString card = ui->cardInput->text().trimmed(); // korttinumero
    QString pin  = ui->pinInput->text().trimmed();  // PIN

    if (card.isEmpty() || pin.isEmpty()) {
        qDebug() << "cardnumber or password missing";
        return;
    }

    // JSON body backendille (Login.js odottaa nämä nimet!)
    QJsonObject json;
    json["cardnumber"] = card;
    json["password"]   = pin;

    QByteArray data = QJsonDocument(json).toJson();
    qDebug() << "POST /login body:" << data;

    // request
    QNetworkRequest request(QUrl("http://localhost:3000/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //  POST
    reply = manager->post(request, data);

    // finished -> slot
    connect(reply, &QNetworkReply::finished, this, &MainWindow::getLoginSlot);
}

void MainWindow::getLoginSlot()
{
    response_data = reply->readAll();
    qDebug() << "LOGIN RESPONSE:" << response_data;

    QJsonObject obj = QJsonDocument::fromJson(response_data).object();
    webToken = obj.value("token").toString();
    qDebug() << "TOKEN:" << webToken;

    if (webToken.isEmpty()) {
        qDebug() << "Login failed:" << obj.value("message").toString();
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->pageMenu);

    reply->deleteLater();
    reply = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_btnDevLogin_clicked()
{
    // DEV: ohitetaan kirjautuminen kehitystä varten
    webToken = "DEV_BYPASS";
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

