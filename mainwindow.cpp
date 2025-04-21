#include "mainwindow.h"
#include <QPainter>//IT WILL CREATE COLOUR IF IMAGE DOES NOT LOAD
#include <QFont>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)//IT WILL SET UP THE WHOLE PROGRAM
    : QMainWindow(parent), adminLogin(nullptr), studentLogin(nullptr)//as it will create or setup after we select a option b/w student and admin login
{
    // Set window size
    resize(700, 600);
    // Load background image
    backgroundImage.load("C:/libfront.jpg");

    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(20);
    // Create title label
    titleLabel = new QLabel("The Enchanted Library", this);
    QFont titleFont("Times New Roman", 36, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white;");
    // Create quote label
    quoteLabel = new QLabel("A library is not just a place to find books; it's a gateway to endless adventures and knowledge.", this);
    QFont quoteFont("Georgia", 14, QFont::StyleItalic);
    quoteLabel->setFont(quoteFont);
    quoteLabel->setAlignment(Qt::AlignCenter);
    quoteLabel->setWordWrap(true);//it is word wrap to enhance the look
    quoteLabel->setStyleSheet("color: white;");
    // Create buttons container
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->setSpacing(15);//SPACE BETWEEN TWO BUTTONS
    // Create Admin button
    adminButton = new QPushButton("Admin", this);
    adminButton->setMinimumSize(150, 50);
    adminButton->setFont(QFont("Arial", 12));
    adminButton->setStyleSheet("QPushButton {"
                               "background-color: #8d6e63;"
                               "color: white;" "border-radius: 5px;""padding: 10px;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: #6d4c41;"
                               "}");

    // Create Student button
    studentButton = new QPushButton("Student", this);
    studentButton->setMinimumSize(150, 50);
    studentButton->setFont(QFont("Arial", 12));
    studentButton->setStyleSheet("QPushButton {"
                                 "background-color: #8d6e63;""color: white;""border-radius: 5px;"
                                 "padding: 10px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #6d4c41;"
                                 "}");

    // Add buttons to button layout
    buttonLayout->addWidget(adminButton);
    buttonLayout->addWidget(studentButton);

    // Add widgets to main layout
    mainLayout->addStretch(1);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(quoteLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);//it is used to mantain the stretchnes of the screen horizontal

    // Connect button signals to slots
    connect(adminButton, &QPushButton::clicked, this, &MainWindow::onAdminButtonClicked);
    connect(studentButton, &QPushButton::clicked, this, &MainWindow::onStudentButtonClicked);
}

MainWindow::~MainWindow()
{
    if (adminLogin) {
        delete adminLogin;
    }
    if (studentLogin) {
        delete studentLogin;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // Draw background image
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
        painter.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 120));
    } else {
        painter.fillRect(0, 0, width(), height(), QColor(50, 50, 50));
    }
    QMainWindow::paintEvent(event);
}

void MainWindow::onAdminButtonClicked()
{
    // Create the admin login window if it doesn't exist
    if (!adminLogin) {
        adminLogin = new AdminLogin(this);
    }

    // Show the admin login window
    adminLogin->show();
    adminLogin->activateWindow();
}

void MainWindow::onStudentButtonClicked()
{
    // Create the student login window if it doesn't exist
    if (!studentLogin) {
        studentLogin = new StudentLogin(this);
    }
    // Show the student login window
    studentLogin->show();
    studentLogin->activateWindow();
}
