#include "adminlogin.h"
#include <QPainter>
#include <QMessageBox>
#include <QGridLayout>
#include "admindashboard.h" // Include the AdminDashboard header

AdminLogin::AdminLogin(QWidget *parent) : QWidget(parent)//main window = parent
{
    // Set window properties
    setWindowTitle("Admin Login");
    resize(700, 600);
    // Load background image
    backgroundImage.load("C:/library_interior.jpg");
    // Create layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);//4 sideed dimension
    mainLayout->setSpacing(20);//4 sided spacing
    // Create title label
    titleLabel = new QLabel("Admin Login", this);
    QFont titleFont("Arial", 24, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #FFFFFF; background-color: rgba(0, 0, 0, 120); padding: 10px; border-radius: 5px;");
    // Create form layout
    QGridLayout *formLayout = new QGridLayout();
    formLayout->setSpacing(15);
    // Create email input
    emailLabel = new QLabel("Email:", this);
    emailLabel->setStyleSheet("color: #FFFFFF; font-size: 14px; font-weight: bold;");
    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Enter admin email");//it take  input the email
    emailEdit->setMinimumHeight(30);
    // Create password input
    passwordLabel = new QLabel("Password:", this);
    passwordLabel->setStyleSheet("color: #FFFFFF; font-size: 14px; font-weight: bold;");
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Enter password");//it take input the password
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(30);
    // Add form elements to layout
    formLayout->addWidget(emailLabel, 0, 0);//row,column
    formLayout->addWidget(emailEdit, 0, 1);
    formLayout->addWidget(passwordLabel, 1, 0);
    formLayout->addWidget(passwordEdit, 1, 1);
    // Create buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);
    //Lgoin Button creations and its stylesheet
    loginButton = new QPushButton("Login", this);
    loginButton->setMinimumSize(100, 40);
    loginButton->setStyleSheet("QPushButton {""background-color: #4CAF50;"
                               "color: white;""border-radius: 5px;""font-size: 14px;""font-weight: bold;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: #45a049;"
                               "}");
    cancelButton = new QPushButton("Cancel", this);
    cancelButton->setMinimumSize(100, 40);
    cancelButton->setStyleSheet("QPushButton {""background-color: #f44336;"
                                "color: white;""border-radius: 5px;""font-size: 14px;""font-weight: bold;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #d32f2f;"
                                "}");
    buttonLayout->addWidget(loginButton);//set dimension of button on the window
    buttonLayout->addWidget(cancelButton);
    buttonLayout->setAlignment(Qt::AlignCenter);
    // Add widgets to main layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch(1);//horizontal stretch
    mainLayout->addLayout(formLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
    // Connect signals and slots
    connect(loginButton, &QPushButton::clicked, this, &AdminLogin::onLoginButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AdminLogin::onCancelButtonClicked);
}
AdminLogin::~AdminLogin()
{
}
void AdminLogin::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // Draw background image
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
        painter.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 120));
    } else {
        painter.fillRect(0, 0, width(), height(), QColor(50, 50, 50));
    }
    QWidget::paintEvent(event);
}
void AdminLogin::onLoginButtonClicked()
{
    QString email = emailEdit->text();
    QString password = passwordEdit->text();
    // Simple validation
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both email and password.");
        return;
    }
    // Check credentials
    QStringList adminEmails = {"ahmed@library.com", "ibrahim@library.com", "maaz@library.com","a@lib.com"};
    // Check if the entered email is in the admin list and the password matches
    if (adminEmails.contains(email) && password == "admin123") {
        QMessageBox::information(this, "Login Successful", "Welcome to the Admin Dashboard!");
        // Create and show the Admin Dashboard
        AdminDashboard *adminDashboard = new AdminDashboard(this);
        adminDashboard->showFullScreen();
        this->close(); // Close the login window
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid email or password. Please try again.");//!!!warninng messsage
    }
}
void AdminLogin::onCancelButtonClicked()
{
    // Clear the fields
    emailEdit->clear();
    passwordEdit->clear();
    // Close the window
    close();
}
