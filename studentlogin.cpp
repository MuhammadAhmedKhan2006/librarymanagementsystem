#include "studentlogin.h"
#include <QPainter>
#include <QMessageBox>
#include <QGridLayout>
#include "studentdashboard.h" // Include the StudentDashboard header

StudentLogin::StudentLogin(QWidget *parent) : QWidget(parent)
{
    // Set window properties
    setWindowTitle("Student Login");
    resize(700, 600);
    // Load background image
    backgroundImage.load("C:/library_interior.jpg");
    // Initialize student credentials
    initializeStudentCredentials();//password and email
    // Set up the login UI
    setupLoginUI();
    // Set up the registration UI
    setupRegistrationUI();
    // Show login form by default
    showLoginForm();
}
StudentLogin::~StudentLogin()
{
}
void StudentLogin::initializeStudentCredentials()
{
    // Initialize the map of student credentials
    studentCredentials["student1@library.com"] = "student123";
    studentCredentials["student2@library.com"] = "password456";
    studentCredentials["student3@library.com"] = "library789";
    studentCredentials["student4@library.com"] = "books2024";
    studentCredentials["student5@library.com"] = "reading567";
    studentCredentials["student6@library.com"] = "studies890";
    studentCredentials["student7@library.com"] = "learn1234";
    studentCredentials["student8@library.com"] = "research55";
    studentCredentials["s9@lib.com"] = "s9";
}
void StudentLogin::setupLoginUI()
{
    // Create login layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);
    // Create title label
    titleLabel = new QLabel("Student Login", this);
    QFont titleFont("Arial", 24, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white; background-color: rgba(0, 0, 0, 120); padding: 10px; border-radius: 5px;");
    // Create form layout
    QGridLayout *formLayout = new QGridLayout();
    formLayout->setSpacing(15);
    // Create email input
    emailLabel = new QLabel("Email:", this);
    emailLabel->setStyleSheet("color: #FFFFFF; font-size: 14px; font-weight: bold;");
    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Enter student email");
    emailEdit->setMinimumHeight(30);
    // Create password input
    passwordLabel = new QLabel("Password:", this);//written beside the box
    passwordLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    passwordEdit = new QLineEdit(this);//boxeds to take input
    passwordEdit->setPlaceholderText("Enter password");//behind
    passwordEdit->setEchoMode(QLineEdit::Password);//keep password secure in (....)
    passwordEdit->setMinimumHeight(30);
    // Add form elements to layout
    //they are setting the alignment of the text in matrix order
    formLayout->addWidget(emailLabel, 0, 0);
    formLayout->addWidget(emailEdit, 0, 1);
    formLayout->addWidget(passwordLabel, 1, 0);
    formLayout->addWidget(passwordEdit, 1,1 );
    // Create buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);
    //Login Button creations and setting stylesheet
    loginButton = new QPushButton("Login", this);
    loginButton->setMinimumSize(100, 40);
    loginButton->setStyleSheet("QPushButton {""background-color: #2196F3;"
                               "color: white;""border-radius: 5px;""font-size: 14px;""font-weight: bold;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: blue;"
                               "}");
    backButton = new QPushButton("Back", this);
    backButton->setMinimumSize(100, 40);
    backButton->setStyleSheet("QPushButton {"
                              "background-color: #f44336;"
                              "color: white;"
                              "border-radius: 5px;"
                              "font-size: 14px;"
                              "font-weight: bold;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: red;"
                              "}");
    registerButton = new QPushButton("Register", this);
    registerButton->setMinimumSize(100, 40);
    registerButton->setStyleSheet("QPushButton {"
                                  "background-color: #4CAF50;"
                                  "color: white;"
                                  "border-radius: 5px;"
                                  "font-size: 14px;"
                                  "font-weight: bold;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: green;"
                                  "}");
    //now we set the alignment of the butttons
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(registerButton);
    buttonLayout->setAlignment(Qt::AlignCenter);
    // Add widgets to main layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch(1);
    mainLayout->addLayout(formLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
    // Connect signals and slots
    connect(loginButton, &QPushButton::clicked, this, &StudentLogin::onLoginButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &StudentLogin::onBackButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &StudentLogin::onRegisterButtonClicked);
}
void StudentLogin::setupRegistrationUI()
{
    // Create registration form widget
    registrationForm = new QWidget(this);
    registrationForm->setGeometry(40, 40, width(), height());//setiing the height and width of the register window
    // Create layout for registration form
    QVBoxLayout *regLayout = new QVBoxLayout(registrationForm);
    regLayout->setContentsMargins(30, 10 , 80 ,80);//setting size in all dimensions
    regLayout->setSpacing(20);
    // Create registration title
    QLabel *regTitleLabel = new QLabel("Student Registration", registrationForm);
    QFont titleFont("Arial", 24, QFont::Bold);
    regTitleLabel->setFont(titleFont);
    regTitleLabel->setAlignment(Qt::AlignCenter);
    regTitleLabel->setStyleSheet("color: #FFFFFF; background-color: rgba(0, 0, 0, 120); padding: 10px; border-radius: 5px;");
    // Create registration form fields
    QGridLayout *regFormLayout = new QGridLayout();
    regFormLayout->setSpacing(15);//setiinng the size of the boxes on the regestration window
    // asking email on regestration form
    QLabel *regEmailLabel = new QLabel("Email:", registrationForm);
    regEmailLabel->setStyleSheet("color: #FFFFFF; font-size: 14px; font-weight: bold;");
    regEmailEdit = new QLineEdit(registrationForm);
    regEmailEdit->setPlaceholderText("Enter your email");
    regEmailEdit->setMinimumHeight(30);
    // Password field
    QLabel *regPasswordLabel = new QLabel("Password:", registrationForm);
    regPasswordLabel->setStyleSheet("color: #FFFFFF; font-size: 14px; font-weight: bold;");
    regPasswordEdit = new QLineEdit(registrationForm);
    regPasswordEdit->setPlaceholderText("Enter password");
    regPasswordEdit->setEchoMode(QLineEdit::Password);
    regPasswordEdit->setMinimumHeight(30);
    // Confirm password field
    QLabel *regConfirmPasswordLabel = new QLabel("Confirm Password:", registrationForm);
    regConfirmPasswordLabel->setStyleSheet("color: #FFFFFF; font-size: 14px; font-weight: bold;");
    regConfirmPasswordEdit = new QLineEdit(registrationForm);
    regConfirmPasswordEdit->setPlaceholderText("Confirm password");
    regConfirmPasswordEdit->setEchoMode(QLineEdit::Password);
    regConfirmPasswordEdit->setMinimumHeight(30);
    // th thing in which we give input is lineedit
    regFormLayout->addWidget(regEmailLabel, 0, 0);//row columns
    regFormLayout->addWidget(regEmailEdit, 0, 1); //(Email label , input Email)
    regFormLayout->addWidget(regPasswordLabel, 1, 0);
    regFormLayout->addWidget(regPasswordEdit, 1, 1);//(Password label , input Password)
    regFormLayout->addWidget(regConfirmPasswordLabel, 2, 0);
    regFormLayout->addWidget(regConfirmPasswordEdit, 2, 1);//(confirm Password label , input confirm Password)
    // Create registration buttons
    QHBoxLayout *regButtonLayout = new QHBoxLayout();
    regButtonLayout->setSpacing(15);
    QPushButton *regSubmitButton = new QPushButton("Submit", registrationForm);
    regSubmitButton->setMinimumSize(100, 40);
    regSubmitButton->setStyleSheet("QPushButton {""background-color: #4CAF50;"
                                   "color: white;""border-radius: 5px;""font-size: 14px;""font-weight: bold;"
                                   "}"
                                   "QPushButton:hover {"
                                   "background-color: #45a049;"
                                   "}");
    QPushButton *regCancelButton = new QPushButton("Cancel", registrationForm);
    regCancelButton->setMinimumSize(100, 40);
    regCancelButton->setStyleSheet("QPushButton {" "background-color: #f44336;"
                                   "color: white;""border-radius: 5px;""font-size: 14px;""font-weight: bold;"
                                   "}"
                                   "QPushButton:hover {"
                                   "background-color: #d32f2f;"//red color
                                   "}");
    regButtonLayout->addWidget(regSubmitButton);
    regButtonLayout->addWidget(regCancelButton);
    regButtonLayout->setAlignment(Qt::AlignCenter);
    // Add widgets to registration layout
    regLayout->addWidget(regTitleLabel);
    regLayout->addStretch(1);//making it horizontally larger
    regLayout->addLayout(regFormLayout);
    regLayout->addStretch(1);
    regLayout->addLayout(regButtonLayout);
    // Connect registration buttons
    connect(regSubmitButton, &QPushButton::clicked, this, &StudentLogin::onRegisterSubmitClicked);
    connect(regCancelButton, &QPushButton::clicked, this, &StudentLogin::onRegisterCancelClicked);
    // Initially hide the registration form
    registrationForm->hide();
}
void StudentLogin::showLoginForm()
{
    // Show login components and hide registration form
    titleLabel->show();
    emailLabel->show();
    emailEdit->show();
    passwordLabel->show();
    passwordEdit->show();
    loginButton->show();
    backButton->show();
    registerButton->show();
    //checking if registration is open so hide it
    if (registrationForm) {
        registrationForm->hide();
    }
}
void StudentLogin::showRegistrationForm()
{
    // Hide login components and show registration form
    titleLabel->hide();
    emailLabel->hide();
    emailEdit->hide();
    passwordLabel->hide();
    passwordEdit->hide();
    loginButton->hide();
    backButton->hide();
    registerButton->hide();
    //opening registrations form
    registrationForm->show();
}
void StudentLogin::paintEvent(QPaintEvent *event)
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
void StudentLogin::onLoginButtonClicked()
{
    QString email = emailEdit->text();
    QString password = passwordEdit->text();
    // Simple validation
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both email and password.");
        return;
    }
    //if student is registered previously
    // Check if the entered email is in the student list and the password matches
    if (studentCredentials.contains(email) && studentCredentials[email] == password) {
        QMessageBox::information(this, "Login Successful", "Welcome to the Student Dashboard!");
        // Create and show the Student Dashboard
        StudentDashboard *studentDashboard = new StudentDashboard(this);
        studentDashboard->showFullScreen();
        this->close(); // Close the login window
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid email or password. Please try again.");//critical means warning!!!
    }
}
void StudentLogin::onBackButtonClicked()
{
    // Clear the fields
    emailEdit->clear();
    passwordEdit->clear();

    // Close the window
    close();
}
void StudentLogin::onRegisterButtonClicked()
{
    // Switch to registration form
    showRegistrationForm();
}
void StudentLogin::onRegisterSubmitClicked()
{
    resize(700,600);
    QString email = regEmailEdit->text();//take text as input
    QString password = regPasswordEdit->text();
    QString confirmPassword = regConfirmPasswordEdit->text();
    // Simple validation
    if (email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "Please fill in all fields.");
        return;
    }
    // Check if passwords match
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Registration Error", "Passwords do not match.");
        return;
    }
    // Check if email is valid format
    if (!email.contains("@") || !email.contains(".")) {
        QMessageBox::warning(this, "Registration Error", "Please enter a valid email address.");
        return;
    }
    // Check if email already exists
    if (studentCredentials.contains(email)) {
        QMessageBox::warning(this, "Registration Error", "This email is already registered.");
        return;
    }
    // Register the new student
    studentCredentials[email] = password;
    QMessageBox::information(this, "Registration Successful",
                             "Your account has been created successfully. Please log in with your new credentials.");
    // Clear registration fields
    regEmailEdit->clear();
    regPasswordEdit->clear();
    regConfirmPasswordEdit->clear();
    // Switch back to login form
    showLoginForm();
}
void StudentLogin::onRegisterCancelClicked()
{
    // Clear registration fields
    regEmailEdit->clear();
    regPasswordEdit->clear();
    regConfirmPasswordEdit->clear();
    // Switch back to login form
    showLoginForm();
}
