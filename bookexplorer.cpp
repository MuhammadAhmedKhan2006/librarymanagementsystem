#include "bookexplorer.h"
#include <QPainter>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>

BookExplorer::BookExplorer(QWidget *parent, bool isDamaged, bool isRecommended)
    : QWidget(parent), isDamaged(isDamaged), isRecommended(isRecommended)
{
    // Set window properties
    if (isDamaged) {
        setWindowTitle("Damaged Books");
    } else if (isRecommended) {
        setWindowTitle("Recommended Books");
    } else {
        setWindowTitle("Explore Books");
    }
    resize(700, 600);
    // Load background image
    backgroundImage.load("C:/Recom&DamageBooks_Library.jpg");
    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);
    // Create title label
    QString titleText = isDamaged ? "Damaged Books" : (isRecommended ? "Recommended Books" : "Explore Books");
    titleLabel = new QLabel(titleText, this);
    QFont titleFont("Arial", 24, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white; background-color: rgba(0, 0, 0, 120); padding: 10px; border-radius: 5px;");
    // Create search layout
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->setSpacing(10);
    //Take input for searching
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search for books...");
    searchEdit->setMinimumHeight(40);
    searchEdit->setStyleSheet("background-color: rgba(255, 255, 255, 200); border-radius: 5px; padding: 5px;");
    searchButton = new QPushButton("Search", this);
    searchButton->setMinimumSize(100, 40);
    searchButton->setStyleSheet("QPushButton {""background-color: #2196F3;"
                                "color: white;""border-radius: 5px;""font-size: 14px;""font-weight: bold;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #0b7dda;"
                                "}");
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);
    // Create books table
    booksTable = new QTableWidget(this);
    booksTable->setColumnCount(5);  // Added a column for the Buy button
    QStringList headers;//headings of column
    headers << "Book Name" << "Author" << "Condition" << "Available" << "Action";
    booksTable->setHorizontalHeaderLabels(headers);
    booksTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    booksTable->setStyleSheet("QTableWidget { background-color: rgba(255, 255, 255, 200); border-radius: 5px; }");
    booksTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    booksTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    booksTable->setAlternatingRowColors(false);
    // Create bought books list
    boughtBooksList = new QListWidget(this);
    boughtBooksList->setStyleSheet("QListWidget { background-color: rgba(255, 255, 255, 200); border-radius: 5px; }");
    boughtBooksList->setVisible(true);  // Hidden by default, show if needed
    // Create buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);
    //Take user back to student dashboard
    backButton = new QPushButton("Back", this);
    backButton->setMinimumSize(100, 40);
    backButton->setStyleSheet("QPushButton {""background-color: #f44336;"
                              "color: white;""border-radius: 5px;""font-size: 14px;""font-weight: bold;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: #d32f2f;"
                              "}");
    buttonLayout->addWidget(backButton);
    buttonLayout->setAlignment(Qt::AlignCenter);
    // Add widgets to main layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(booksTable);
    mainLayout->addWidget(boughtBooksList);  // Add list widget but it's hidden
    mainLayout->addLayout(buttonLayout);
    // Connect signals and slots
    connect(backButton, &QPushButton::clicked, this, &BookExplorer::onBackButtonClicked);
    connect(searchButton, &QPushButton::clicked, this, &BookExplorer::onSearchButtonClicked);
    // Setup initial books based on the type
    if (isDamaged) {
        setupDamagedBooks();
    } else if (isRecommended) {
        setupRecommendedBooks();
    } else {
        setupInitialBooks();
    }
}
BookExplorer::~BookExplorer()
{
}
void BookExplorer::paintEvent(QPaintEvent *event)
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
void BookExplorer::onBackButtonClicked()
{
    this->close();
    this->parentWidget()->show(); // Show the previous window
}
void BookExplorer::onBuyButtonClicked(int row)//it is declared to select the row to buy the book
{
    // Implementation for buying a book
    if (row >= 0 && row < booksTable->rowCount()) {
        QString bookName = booksTable->item(row, 0)->text();
        QString author = booksTable->item(row, 1)->text();
        // Add the book to the bought books list
        QString bookInfo = bookName + " by " + author;
        boughtBooksList->addItem(bookInfo);
        // Show a confirmation message
        QMessageBox::information(this, "Purchase", "You have purchased: " + bookName);
        // Option: You could disable the buy button after purchase
        if (QPushButton* buyButton = qobject_cast<QPushButton*>(booksTable->cellWidget(row, 4))) {//4 means last column of buy
            //qobject_cast is calling push button
            buyButton->setEnabled(false);
            buyButton->setText("Purchased");
        }
    }
}
void BookExplorer::onSearchButtonClicked()
{
    QString searchText = searchEdit->text();
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Search", "Please enter a search term.");
        return;
    }
    // Filter the table based on search text
    for (int i = 0; i < booksTable->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < booksTable->columnCount() - 1; ++j) {  // Skip the Action column
            QTableWidgetItem *item = booksTable->item(i, j);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {//it will check for the book that is searched by user
                match = true;
                break;
            }
        }
        booksTable->setRowHidden(i, !match);
    }
}
void BookExplorer::setupInitialBooks()
{
    // Add some initial books
    addBookToTable("The Treasure Island", "Robert Louis Stevenson", "Excellent", true);
    addBookToTable("The Prisoner of Zenda", "Anthony Hope Hawkins", "Good", true);
    addBookToTable("To Kill a Mockingbird", "Harper Lee", "Good", true);
    addBookToTable("1984", "George Orwell", "Excellent", true);
    addBookToTable("The Great Gatsby", "F. Scott Fitzgerald", "Good", true);
    addBookToTable("Pride and Prejudice", "Jane Austen", "Fair", true);
    addBookToTable("The Catcher in the Rye", "J.D. Salinger", "Good", true);
}
void BookExplorer::setupDamagedBooks()
{
    // Add damaged books
    addBookToTable("Crime and Punishment", "Fyodor Dostoevsky", "Damaged", false);
    addBookToTable("The Kidnap", "Robert Louis Stevenson", "Damaged", false);
    addBookToTable("War and Peace ", "Leo Tolstoy", "Damaged", false);
    addBookToTable("My Biography", "Mark Robert", "Damaged", false);
}
void BookExplorer::setupRecommendedBooks()
{
    // Add recommended books
    addBookToTable("The Treasure Island", "Robert Louis Stevenson", "Excellent", true);
    addBookToTable("The Prisoner of Zenda", "Anthony Hope Hawkins", "Good", true);
    addBookToTable("To Kill a Mockingbird", "Harper Lee", "Good", true);
    addBookToTable("1984", "George Orwell", "Excellent", true);
}
void BookExplorer::addBookToTable(const QString &name, const QString &author, const QString &condition, bool available)
{
    int row = booksTable->rowCount();
    booksTable->insertRow(row);
    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *authorItem = new QTableWidgetItem(author);
    QTableWidgetItem *conditionItem = new QTableWidgetItem(condition);
    QTableWidgetItem *availableItem = new QTableWidgetItem(available ? "Yes" : "No");
    booksTable->setItem(row, 0, nameItem);
    booksTable->setItem(row, 1, authorItem);
    booksTable->setItem(row, 2, conditionItem);
    booksTable->setItem(row, 3, availableItem);
    // Add a buy button if the book is available
    if (available) {
        QPushButton *buyButton = new QPushButton("Buy");
        buyButton->setStyleSheet("QPushButton {""background-color: #4CAF50;"
                                 "color: white;""border-radius: 3px;""padding: 3px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #45a049;"
                                 "}");
        // Connect the button to onBuyButtonClicked slot with the current row
        connect(buyButton, &QPushButton::clicked, [this, row]() {
            this->onBuyButtonClicked(row);
        });
        booksTable->setCellWidget(row, 4, buyButton);//set the buy button on column 4
    } else {
        // For unavailable books, add a disabled button
        QPushButton *notAvailableButton = new QPushButton("Not Available");
        notAvailableButton->setEnabled(false);
        notAvailableButton->setStyleSheet("QPushButton {""background-color: #cccccc;"
                                          "color: #666666;""border-radius: 3px;""padding: 3px;"
                                          "}");
        booksTable->setCellWidget(row, 4, notAvailableButton);
    }
}
