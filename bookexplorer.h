#ifndef BOOKEXPLORER_H
#define BOOKEXPLORER_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLineEdit>
#include <QTableWidget>
#include <QListWidget>
class BookExplorer : public QWidget
{
    Q_OBJECT
public:
    explicit BookExplorer(QWidget *parent = nullptr, bool isDamaged = false, bool isRecommended = false);
    ~BookExplorer();//where there is a explicit, there will be a destructor
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onBackButtonClicked();//back to the student dashboard
    void onBuyButtonClicked(int row); // Ensure this is declared
    void onSearchButtonClicked(); //Search the books title entered in searchEdit
private:
         //Labels
    QLabel *titleLabel;
    //LineEdits
    QLineEdit *searchEdit;
    //QPushbutton
    QPushButton *searchButton;
    QPushButton *backButton;
    //TableWidget
    QTableWidget *booksTable;
    //ListWidgets
    QListWidget *boughtBooksList;
    //QPixmap
    QPixmap backgroundImage;
    //Functions
    bool isDamaged;
    bool isRecommended;
    void setupInitialBooks();
    void setupDamagedBooks();
    void setupRecommendedBooks();
    void addBookToTable(const QString &name, const QString &author, const QString &condition, bool available);
};
#endif // BOOKEXPLORER_H
