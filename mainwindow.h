#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QWidget>
#include "adminlogin.h"
#include "studentlogin.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onAdminButtonClicked();
    void onStudentButtonClicked();
private:
    //Labels
    QLabel *titleLabel;
    QLabel *quoteLabel;
    //QPushButton
    QPushButton *adminButton;
    QPushButton *studentButton;
    QPixmap backgroundImage;
    // Login windows
    AdminLogin *adminLogin;
    StudentLogin *studentLogin;
};
#endif // MAINWINDOW_H
