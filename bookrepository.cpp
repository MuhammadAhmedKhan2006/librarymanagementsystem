// bookrepository.cpp
#include "bookrepository.h"
#include "admindashboard.h"
void BookRepository::addBook(const Book &book)
{
    books[book.name] = book;//storing the name of books
    emit bookAdded(book);//emit is a keyword, in this bookAdded will return book to student dashboard
    emit booksChanged();//similarly  it will append the book
}
QVector<Book> BookRepository::getAllBooks() const
{
    QVector<Book> result;
    for (auto it = books.begin(); it != books.end(); ++it) {//auto is an initializer of it iterator
        result.append(it.value());//it will store the current  value at the iterator
        //append is a function which is used to add elements such as an array
    }
    return result;
}
Book BookRepository::getBook(const QString &bookName) const
{
    if (books.contains(bookName)) {
        return books[bookName];//as we are searching by name
    }
    return Book();
}
bool BookRepository::hasBook(const QString &bookName) const
{
    return books.contains(bookName);
}
QString BookRepository::getPdfPath(const QString &bookName) const
{
    if (books.contains(bookName) && !books[bookName].pdfPath.isEmpty()) {
        return books[bookName].pdfPath;
    }
    return QString();
}

void BookRepository::updateBookStatus(const QString &bookName, const QString &status)
{
    if (books.contains(bookName)) {
        books[bookName].status = status;
        emit booksChanged();
    }
}

void BookRepository::updateBookDueDate(const QString &bookName, const QString &dueDate)
{
    if (books.contains(bookName)) {
        books[bookName].dueDate = dueDate;
        emit booksChanged();
    }
}
