#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString currentCardType; // "DEBIT" or "CREDIT"

    // Card information from login
    QString cardNumber;
    QString accountHolder;
    QString cardType;
    QString webToken; // JWT


private slots:
    void on_btnLogin_clicked();
    void getLoginSlot();
    void on_btnDebitSelected();
    void on_btnCreditSelected();
    void on_btnDevLogin_clicked();
    void on_btnBackToLogin_clicked();
};

#endif // MAINWINDOW_H
