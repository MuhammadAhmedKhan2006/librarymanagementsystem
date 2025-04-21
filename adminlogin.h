#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
class AdminLogin : public QWidget
{
    Q_OBJECT
public:
    explicit AdminLogin(QWidget *parent = nullptr);
    ~AdminLogin();
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onLoginButtonClicked();
    void onCancelButtonClicked();
private:
    //Labels
    QLabel *titleLabel;
    QLabel *emailLabel;
    QLabel *passwordLabel;
    //LineEdits
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    //QPushButton
    QPushButton *loginButton;
    QPushButton *cancelButton;
    //QPixmap to set background Image
    QPixmap backgroundImage;
};
#endif // ADMINLOGIN_H
