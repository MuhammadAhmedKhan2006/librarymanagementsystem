// bookrepository.h
#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H
#include <QObject>
#include <QMap>
#include <QString>
#include <QVector>
// Book structure to hold all book information
struct Book {
    QString name;
    QString author;
    QString isbn;
    QString condition;
    QString status; // "Available", "Checked Out", etc.
    QString pdfPath;
    bool hasPdf;
    double price;       // Added price field
    double rentPrice;   // Added rentPrice field
    QString dueDate;    // Added dueDate field
    //constructor  n this case, it indicates that by default, the book does not have a PDF version.
    Book() : hasPdf(false), price(00.0), rentPrice(0.0) {}
    Book(const QString &name, const QString &author, const QString &isbn = "",
         const QString &condition = "Good", const QString &status = "Available",
         const QString &pdfPath = "", double price = 80.0, double rentPrice = 3.0,
         const QString &dueDate = "")
        : name(name), author(author), isbn(isbn), condition(condition),
        status(status), pdfPath(pdfPath), hasPdf(!pdfPath.isEmpty()),
        price(price), rentPrice(rentPrice), dueDate(dueDate) {}
};
class BookRepository : public QObject
{
    Q_OBJECT
public:
    static BookRepository* getInstance() {
        static BookRepository instance; //static means it can only used in this class only.
        return &instance;//instance is a variable and & shows the address of the variable
        //object is called as an instance
        //getInstance is the function which provide access to the object
    }
    // Add a book to the repository
    void addBook(const Book &book);
    // Get all books
    QVector<Book> getAllBooks() const;
    // Get book by name
    Book getBook(const QString &bookName) const;
    // Check if book exists
    bool hasBook(const QString &bookName) const;
    // Get PDF path for a book
    QString getPdfPath(const QString &bookName) const;
    // Update book status
    void updateBookStatus(const QString &bookName, const QString &status);
    // Update book due date
    void updateBookDueDate(const QString &bookName, const QString &dueDate);
signals:
    void bookAdded(const Book &book);//add books to student by the help of object
    void booksChanged();//checks the book which are being changed
private:
    BookRepository(QObject *parent = nullptr) : QObject(parent) {}
    ~BookRepository() {}
    BookRepository(const BookRepository&) = delete;
    BookRepository& operator=(const BookRepository&) = delete;
    QMap<QString, Book> books;
};
#endif // BOOKREPOSITORY_H
