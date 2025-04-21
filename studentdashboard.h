#ifndef STUDENTDASHBOARD_H
#define STUDENTDASHBOARD_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QDateEdit>
#include <QSpinBox>
#include <QInputDialog>

// Forward declaration
class Book;
class BookExplorer;

class StudentDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit StudentDashboard(QWidget *parent = nullptr);
    ~StudentDashboard();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onSearchButtonClicked();
    void onRecommendedBooksButtonClicked();
    void onViewBookButtonClicked();
    void onBuyBookButtonClicked(); // New slot for Buy button
    void onRentBookButtonClicked();
    void onReturnBookButtonClicked();
    void onCheckoutButtonClicked();
    void onLogoutButtonClicked();
    void onBookAdded(const Book &book);
    void refreshBookTable();
    void updateTotalPrice();

private:
    void addBookToTable(const QString &name, const QString &author, const QString &condition, bool available, double price, double rentPrice);

    QPixmap backgroundImage;
    QLabel *titleLabel;
    QLabel *welcomeLabel;
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QTableWidget *booksTable;
    QPushButton *recommendedBooksButton;
    QPushButton *viewBookButton;
    QPushButton *buyBookButton; // New button for Buy functionality
    QPushButton *rentBookButton;
    QPushButton *returnBookButton;
    QPushButton *checkoutButton;
    QPushButton *logoutButton;
    BookExplorer *bookExplorer;

    // Widgets for rent functionality
    QLabel *totalPriceLabel;
    QTableWidget *cartTable;
    QLabel *rentalDaysLabel;
    QSpinBox *rentalDaysSpinBox;

    // Cart and pricing tracking
    QVector<QPair<QString, double>> cartItems; // Book name and price
    QVector<QPair<QString, double>> rentedBooks; // Book name and rent price
    double totalPrice;
};

#endif // STUDENTDASHBOARD_H
