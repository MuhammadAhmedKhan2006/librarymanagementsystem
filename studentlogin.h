#ifndef STUDENTLOGIN_H
#define STUDENTLOGIN_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMap>

class StudentLogin : public QWidget
{
    Q_OBJECT
public:
    explicit StudentLogin(QWidget *parent = nullptr);
    ~StudentLogin();
protected:
    void paintEvent(QPaintEvent *event) override;//it is overriding the paintEvent function defined in the QWidget
private slots:
    void onLoginButtonClicked();
    void onBackButtonClicked();
    void onRegisterButtonClicked();
    void onRegisterSubmitClicked();
    void onRegisterCancelClicked();
private:
    // Main login UI components
    //Labels
    QLabel *titleLabel;
    QLabel *emailLabel;
    QLabel *passwordLabel;
    //LineEdits
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    //PushButton
    QPushButton *loginButton;
    QPushButton *backButton;
    QPushButton *registerButton;
    //QPixmap
    QPixmap backgroundImage;
    // Registration form UI components
    QWidget *registrationForm;    //set up QWidget for Registration form
    //LineEdits for Registration form
    QLineEdit *regEmailEdit;
    QLineEdit *regPasswordEdit;
    QLineEdit *regConfirmPasswordEdit;
    // Student credentials storage
    QMap<QString, QString> studentCredentials;
    // Helper methods
    void setupLoginUI();  //it is function used to set up the Login form UI
    void setupRegistrationUI();  //it is function usd to setup the Registration form UI
    void showLoginForm();      //shows login Form
    void showRegistrationForm(); //Show Registration form
    void initializeStudentCredentials();//Save the Credentials(Passwords and Emails) of students
};

#endif // STUDENTLOGIN_H
