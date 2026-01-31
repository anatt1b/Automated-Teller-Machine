#include "cardselectionpage.h"
#include <QMessageBox>

CardSelectionPage::CardSelectionPage(QWidget *parent)
    : QWidget(parent), creditFeatureEnabled(true)
{
    setupUI();
    applyStyles();
}

CardSelectionPage::~CardSelectionPage()
{
}

void CardSelectionPage::setupUI()
{
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);

    // Header section
    titleLabel = new QLabel("Select Transaction Type", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #333;");

    subtitleLabel = new QLabel("Choose how you would like to proceed", this);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("font-size: 16px; color: #666;");

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(subtitleLabel);
    mainLayout->addSpacing(20);

    // Card info frame
    cardInfoFrame = new QFrame(this);
    cardInfoFrame->setFrameShape(QFrame::StyledPanel);

    QVBoxLayout *cardInfoLayout = new QVBoxLayout(cardInfoFrame);
    cardInfoLayout->setContentsMargins(20, 20, 20, 20);

    cardNumberLabel = new QLabel("•••• •••• •••• 4532", this);
    cardNumberLabel->setStyleSheet("font-size: 18px; font-weight: 600; color: #333; letter-spacing: 2px;");

    accountHolderLabel = new QLabel("JOHN DOE", this);
    accountHolderLabel->setStyleSheet("font-size: 14px; color: #666; margin-top: 8px;");

    cardInfoLayout->addWidget(cardNumberLabel);
    cardInfoLayout->addWidget(accountHolderLabel);

    mainLayout->addWidget(cardInfoFrame);
    mainLayout->addSpacing(10);

    // Card option buttons layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(20);

    // Debit button
    debitButton = new QPushButton("💳\n\nDebit\n\nUse your checking account balance\n\nAvailable", this);
    debitButton->setMinimumHeight(200);
    debitButton->setCursor(Qt::PointingHandCursor);
    connect(debitButton, &QPushButton::clicked, this, &CardSelectionPage::onDebitClicked);

    // Credit button
    creditButton = new QPushButton("💎\n\nCredit\n\nUse your credit line\n\nAvailable", this);
    creditButton->setMinimumHeight(200);
    creditButton->setCursor(Qt::PointingHandCursor);
    connect(creditButton, &QPushButton::clicked, this, &CardSelectionPage::onCreditClicked);

    buttonsLayout->addWidget(debitButton);
    buttonsLayout->addWidget(creditButton);

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addSpacing(10);

    // Back button
    backButton = new QPushButton("← Back to Login", this);
    backButton->setMinimumHeight(50);
    backButton->setCursor(Qt::PointingHandCursor);
    connect(backButton, &QPushButton::clicked, this, &CardSelectionPage::onBackClicked);

    mainLayout->addWidget(backButton);

    // Note label
    noteLabel = new QLabel("Your selection will determine the account used for this transaction", this);
    noteLabel->setAlignment(Qt::AlignCenter);
    noteLabel->setStyleSheet("font-size: 13px; color: #999; font-style: italic; margin-top: 10px;");
    noteLabel->setWordWrap(true);

    mainLayout->addWidget(noteLabel);

    setLayout(mainLayout);
}

void CardSelectionPage::applyStyles()
{
    // Set window background
    setStyleSheet("QWidget { background-color: white; }");

    // Card info frame style
    cardInfoFrame->setStyleSheet(
        "QFrame {"
        "   background-color: #f8f9fa;"
        "   border-radius: 12px;"
        "   border-left: 4px solid #667eea;"
        "}"
        );

    // Debit button style
    debitButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #667eea, stop:1 #764ba2);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 15px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 20px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #7c92f0, stop:1 #8a5db8);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #5568d3, stop:1 #653a8e);"
        "}"
        );

    // Credit button style
    creditButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #f093fb, stop:1 #f5576c);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 15px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 20px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #f5a5fc, stop:1 #f76b7f);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #e881ea, stop:1 #e34359);"
        "}"
        "QPushButton:disabled {"
        "   background: #e0e0e0;"
        "   color: #999;"
        "}"
        );

    // Back button style
    backButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #f8f9fa;"
        "   border: 2px solid #e0e0e0;"
        "   border-radius: 10px;"
        "   color: #666;"
        "   font-size: 16px;"
        "   font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e0e0e0;"
        "   border-color: #ccc;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #d0d0d0;"
        "}"
        );
}

void CardSelectionPage::setCardInfo(const QString &cardNumber, const QString &accountHolder, bool hasCreditFeature)
{
    // Display last 4 digits of card number
    QString maskedNumber = "•••• •••• •••• " + cardNumber.right(4);
    cardNumberLabel->setText(maskedNumber);
    accountHolderLabel->setText(accountHolder.toUpper());

    // Enable or disable credit feature
    creditFeatureEnabled = hasCreditFeature;
    creditButton->setEnabled(hasCreditFeature);

    if (!hasCreditFeature) {
        creditButton->setText("💎\n\nCredit\n\nUse your credit line\n\nNot Available");
        creditButton->setCursor(Qt::ForbiddenCursor);
    } else {
        creditButton->setText("💎\n\nCredit\n\nUse your credit line\n\nAvailable");
        creditButton->setCursor(Qt::PointingHandCursor);
    }
}

void CardSelectionPage::onDebitClicked()
{
    emit debitSelected();
}

void CardSelectionPage::onCreditClicked()
{
    if (!creditFeatureEnabled) {
        QMessageBox::information(this, "Credit Not Available",
                                 "Credit feature is not available for this card.");
        return;
    }

    emit creditSelected();
}

void CardSelectionPage::onBackClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Logout",
        "Are you sure you want to go back to login?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        emit backButtonClicked();
    }
}
