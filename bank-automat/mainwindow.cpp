#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QMessageBox>

#include <QFile>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly)) {
        QString style = QLatin1String(file.readAll());
        qApp->setStyleSheet(style);
        file.close();
    }

    ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    manager = new QNetworkAccessManager(this);
    // connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::on_btnLogin_clicked);


    // Connect card selection page buttons
    connect(ui->debit, &QPushButton::clicked, this, &MainWindow::on_btnDebitSelected);
    connect(ui->credit, &QPushButton::clicked, this, &MainWindow::on_btnCreditSelected);


    connect(ui->btnBalance, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageBalance);
        if (selectedAccountId < 0 || customerId < 0) return;

        // TESTI PRINTTI
        qDebug() << "Balance click accountId:" << selectedAccountId << "customerId:" << customerId;
        qDebug() << "GET URL:" << QString("http://localhost:3000/account/%1/%2").arg(selectedAccountId).arg(customerId);


        QNetworkRequest request(QUrl(QString("http://localhost:3000/account/%1/%2")
                                         .arg(selectedAccountId).arg(customerId)));
        request.setRawHeader("Authorization", QByteArray("Bearer ") + webToken.toUtf8());

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &MainWindow::getBalanceSlot);
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

    connect(ui->btnCreditWithdraw, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->CreditWithdraw);
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
    qDebug() << "LOGIN CLICK";

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
    qDebug() << "Created reply ptr:" << reply;


    // finished -> slot
    connect(reply, &QNetworkReply::finished, this, &MainWindow::getLoginSlot);
}

void MainWindow::getLoginSlot()
{
    // FIX: always use the reply thath emitted the signal ( prevents nullptf / wrong reply crash)
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    if (!r) return;

    response_data = r->readAll();
    qDebug() << "LOGIN RESPONSE:" << response_data;

    QJsonObject obj = QJsonDocument::fromJson(response_data).object();
    accounts = obj.value("accounts").toArray(); // store [{account_id, account_type}]
    customerId = obj.value("customer_id").toInt(-1); // only if backend returns it
    webToken = obj.value("token").toString();
    qDebug() << "TOKEN:" << webToken;

    if (webToken.isEmpty()) {
        qDebug() << "Login failed:" << obj.value("message").toString();
        QMessageBox::critical(this, "Login Failed", obj.value("message").toString());
        r->deleteLater();
        return;
    }

    // Get card information from response
    cardNumber = obj.value("cardnumber").toString();
    accountHolder = obj.value("account_holder").toString("ACCOUNT HOLDER");

    // Get card type: "debit", "credit", or "combo"
    cardType = obj.value("card_TYPE").toString("yhdistelmä").toLower();

    qDebug() << "RAW card_TYPE:" << obj.value("card_TYPE").toString();
    qDebug() << "cardType len:" << cardType.length();
    qDebug() << "Card Type:" << cardType;

    // Route based on card type
    if (cardType == "debit") {
        // Debit only card - go directly to menu with DEBIT selected
        currentCardType = "DEBIT";
        // pick DEBIT account id
        for (const auto &a : accounts){
            QJsonObject o = a.toObject();
            if (o.value("account_type").toString() == "DEBIT"){
                selectedAccountId = o.value("account_id").toInt(-1);
                break;
            }
        }
        qDebug() << "Debit-only card detected, going directly to menu";

        // TESTI PRINTTI
        qDebug() << "selectedAccountId:" << selectedAccountId << "customerId:" << customerId;
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);

    } else if (cardType == "credit") {
        // Credit only card - go directly to menu with CREDIT selected
        currentCardType = "CREDIT";
        // pick CREDIT account id

        selectedAccountId = -1;
        qDebug() << "ACCOUNTS from login:" << QJsonDocument(accounts).toJson(QJsonDocument::Compact);

        for (const auto &a : accounts) {
            QJsonObject o = a.toObject();

            const QString type = o.value("account_type").toString().trimmed().toUpper();
            const int id = o.value("account_id").toInt(-1);

            qDebug() << "account row:" << o << "type=" << type << "id=" << id;

            if (type == "CREDIT") {
                selectedAccountId = id;
                break;
            }

        }
        qDebug() << "Credit-only card detected, going directly to menu";

        // TESTI PRINTTI
        qDebug() << "selectedAccountId:" << selectedAccountId << "customerId:" << customerId;
        ui->stackedWidget->setCurrentWidget(ui->creditMenu);
        // Fetch credit limmit for credit account when entering creditMenu
        if (selectedAccountId >= 0 && customerId >= 0){
            QNetworkRequest request(QUrl(QString("http://localhost:3000/account/%1/%2")
                                             .arg(selectedAccountId).arg(customerId)));
            request.setRawHeader("Authorization", QByteArray("Bearer ") + webToken.toUtf8());

            reply = manager->get(request);
            connect(reply, &QNetworkReply::finished, this, &MainWindow::getCreditLimitSlot);
        }

    } else {
        // Combo card (or default) - show card selection page
        qDebug() << "Combo card detected, showing card selection page";

        // Set card info on the card selection page
        QString maskedNumber = "•••• •••• •••• " + cardNumber.right(4);
        ui->cardInput->setText(maskedNumber);


        // Enable both buttons for combo card
        ui->debit->setEnabled(true);
        ui->credit->setEnabled(true);
        ui->debit->setText("\n\nDEBIT\n\nUse checking account");
        ui->credit->setText("\n\nCREDIT\n\nUse credit line");

        // TESTI PRINTTI
        qDebug() << "selectedAccountId:" << selectedAccountId;


        // Navigate to card selection page
        ui->stackedWidget->setCurrentWidget(ui->pageCardSelection);
    }

    r->deleteLater();
    // reply = nullptr;
}

void MainWindow::on_btnDebitSelected()
{
    currentCardType = "DEBIT";
    qDebug() << "Debit card selected";
    // pick DEBIT account id
    selectedAccountId = -1;
    for(const auto &a : accounts){
        QJsonObject o = a.toObject();
        if(o.value("account_type").toString()=="DEBIT"){
            selectedAccountId = o.value("account_id").toInt(-1);
            break;
        }
    }
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
    // pick CREDIT account id
    selectedAccountId = -1;
    qDebug() << "ACCOUNTS from login:" << QJsonDocument(accounts).toJson(QJsonDocument::Compact);

    for(const auto &a : accounts){
        QJsonObject o = a.toObject();

        const QString type = o.value("account_type").toString().trimmed().toUpper();
        const int id = o.value("account_id").toInt(-1);
        qDebug() << "account row: "<< o <<"type=" << type << "id=" << id;

        if (type == "CREDIT"){
            selectedAccountId = id;
            break;
        }
        qDebug() << "Picked CREDIT account_id =" << selectedAccountId << "customerId =" << customerId;

    }
    ui->stackedWidget->setCurrentWidget(ui->creditMenu);
    // Fetch credit limmit for credit account when entering creditMenu
    if (selectedAccountId >= 0 && customerId >= 0){
        QNetworkRequest request(QUrl(QString("http://localhost:3000/account/%1/%2")
                                         .arg(selectedAccountId).arg(customerId)));
        request.setRawHeader("Authorization", QByteArray("Bearer ") + webToken.toUtf8());

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &MainWindow::getCreditLimitSlot);
    }
}

void MainWindow::getBalanceSlot()
{
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    if (!r) return;

    response_data = r->readAll();

    //TESTI PRINTTI
    qDebug() << "BALANCE RESPONSE RAW:" << response_data;
    qDebug() << "HTTP status:" << r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Network error:" << r->error() << r->errorString();


    QJsonDocument doc = QJsonDocument::fromJson(response_data);
    QJsonObject obj = doc.isArray() ? doc.array().first().toObject() : doc.object();

    double balance = obj.value("balance").toString().toDouble();
    double dailyLimit = obj.value("daily_withdraw_limit").toDouble();
    double dailyLeft = obj.value("daily_limit_left").toString().toDouble();

    ui->lblBalanceValue->setText(QString::number(balance, 'f', 2));
    ui->lblWithdrawLimitValue->setText(QString::number(dailyLimit, 'f', 2));
    ui->lblDailyLimitLeft->setText(QString::number(dailyLeft, 'f', 2));

    r->deleteLater();
}

void MainWindow::on_btnBackToLogin_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Logout",
        "Are you sure you want to go back to login?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        webToken.clear();
        currentCardType.clear();
        cardType.clear();
        ui->cardInput->clear();
        ui->pinInput->clear();
        ui->stackedWidget->setCurrentWidget(ui->pageLogin);
    }
}

void MainWindow::getCreditLimitSlot()
{
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    if (!r)return;

    response_data = r->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(response_data);
    QJsonObject obj = doc.isArray() ? doc.array().first().toObject() : doc.object();

    double creditLimit = obj.value("credit_limit").toString().toDouble();
    double availableCredit = obj.value("available_credit").toDouble();
    ui->lblCreditLimit->setText(QString::number(creditLimit, 'f', 2));
    ui->lblAvailableCredit->setText(QString::number(availableCredit, 'f', 2));
    r->deleteLater();
}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_btnDevLogin_clicked()
{
    // DEV: ohitetaan kirjautuminen kehitystä varten
    webToken = "DEV_BYPASS";

    // Set dummy card info for dev login - TEST COMBO CARD
    cardNumber = "4532123456789012";
    accountHolder = "DEV USER";

    cardType = "YHDISTELMA";  // Change this to test: "debit", "credit", or "combo"

    cardType = "debit";  // Change this to test: "debit", "credit", or "combo"


    qDebug() << "DevLogin - Card Type:" << cardType;

    // Route based on card type
    if (cardType == "debit") {
        currentCardType = "DEBIT";
        qDebug() << "Dev: Debit-only card, going to menu";
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);

    } else if (cardType == "credit") {
        currentCardType = "CREDIT";
        qDebug() << "Dev: Credit-only card, going to menu";
        ui->stackedWidget->setCurrentWidget(ui->creditMenu);

    } else {
        // Combo card - show selection page
        qDebug() << "Dev: Combo card, showing selection";
        QString maskedNumber = "•••• •••• •••• " + cardNumber.right(4);
        ui->cardInput->setText(maskedNumber);
        ui->debit->setEnabled(true);
        ui->credit->setEnabled(true);
        ui->debit->setText("\n\nDEBIT\n\nUse checking account");
        ui->credit->setText("\n\nCREDIT\n\nUse credit line");

        ui->stackedWidget->setCurrentWidget(ui->pageCardSelection);
    }
}



