#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    manager = new QNetworkAccessManager(this);
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::on_btnLogin_clicked);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::getLoginSlot);

    // Connect card selection page buttons
    connect(ui->debit, &QPushButton::clicked, this, &MainWindow::on_btnDebitSelected);
    connect(ui->credit, &QPushButton::clicked, this, &MainWindow::on_btnCreditSelected);


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
    // Get card information from response
    cardNumber = obj.value("cardnumber").toString();
    hasCreditFeature = obj.value("has_credit").toBool(true); // default true if not provided

    // Set card info on the card selection page
    QString maskedNumber = "•••• •••• •••• " + cardNumber.right(4);
    ui->cardInput->setText(maskedNumber);


    // Enable/disable credit button based on card feature
    ui->credit->setEnabled(hasCreditFeature);
    if (!hasCreditFeature) {
        ui->credit->setText("CREDIT\n(Not Available)");
    } else {
        ui->credit->setText("CREDIT");
    }

    // Navigate to card selection page
    ui->stackedWidget->setCurrentWidget(ui->pageCardSelection);
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    ui->stackedWidget->setCurrentWidget(ui->creditMenu);

        reply->deleteLater();
    reply = nullptr;
}
    void MainWindow::on_btnDebitSelected()
    {
        currentCardType = "DEBIT";
        qDebug() << "Debit card selected";
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    }

    void MainWindow::on_btnCreditSelected()
    {
        if (!ui->credit->isEnabled()) {
            QMessageBox::information(this, "Credit Not Available",
                                     "Credit feature is not available for this card.");
            return;
        }

        currentCardType = "CREDIT";
        qDebug() << "Credit card selected";
        ui->stackedWidget->setCurrentWidget(ui->creditMenu);
    }
    void MainWindow::on_btnBackToLogin_clicked()
    {

    webToken.clear();
    currentCardType.clear();
    ui->cardInput->clear();
    ui->pinInput->clear();
    ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    }


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_btnDevLogin_clicked()
{
    // DEV: ohitetaan kirjautuminen kehitystä varten
    webToken = "DEV_BYPASS";
    ui->stackedWidget->setCurrentWidget(ui->pageCardSelection);
    ui->credit->setEnabled(true);
    ui->credit->setText("CREDIT");

}

