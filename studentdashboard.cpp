#include "studentdashboard.h"
#include "bookexplorer.h"
#include "bookrepository.h"
#include <QPainter>
#include <QHeaderView>
#include <QMessageBox>
#include <QDate>
#include <QGroupBox>
#include <QScrollArea>
#include <QScreen>
#include <QApplication>

StudentDashboard::StudentDashboard(QWidget *parent) : QWidget(parent), totalPrice(0.0)
{
    // Set window properties
    setWindowTitle("Student Dashboard");

    // Fixed size for dialog
    setFixedSize(700, 600);

    // Load background image
    backgroundImage.load("C:/library_dasboard.jpg");

    // Create main layout with scroll area for better responsiveness
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget *scrollWidget = new QWidget();
    scrollArea->setWidget(scrollWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(scrollWidget);
    mainLayout->setContentsMargins(15, 15, 15, 15);  // Reduced padding
    mainLayout->setSpacing(10);  // Reduced spacing between elements

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scrollArea);

    // Create title label - smaller font
    titleLabel = new QLabel("Student Dashboard", this);
    QFont titleFont("Arial", 18, QFont::Bold);  // Reduced font size
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #FFFFFF; background-color: rgba(0, 0, 0, 120); padding: 8px; border-radius: 6px;");

    // Create welcome label - smaller font
    welcomeLabel = new QLabel("Welcome to the Enchanted Library. What would you like to do today?", this);
    QFont welcomeFont("Georgia", 12);  // Reduced font size
    welcomeLabel->setFont(welcomeFont);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("color: #FFFFFF; text-shadow: 1px 1px 2px #000000;");

    // Create search layout with reduced spacing
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->setSpacing(10);

    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search for books...");
    searchEdit->setMinimumHeight(30);  // Reduced height
    searchEdit->setStyleSheet("background-color: rgba(255, 255, 255, 200); border-radius: 5px; padding: 4px; font-size: 12px;");

    searchButton = new QPushButton("Search", this);
    searchButton->setMinimumSize(80, 30);  // Reduced size
    searchButton->setStyleSheet("QPushButton {"
                                "background-color: #2196F3;"
                                "color: white;"
                                "border-radius: 5px;"
                                "font-size: 12px;"
                                "font-weight: bold;"
                                "padding: 4px;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #0b7dda;"
                                "}");

    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);

    // Create books table with additional price columns
    booksTable = new QTableWidget(this);
    booksTable->setColumnCount(6);
    QStringList headers;
    headers << "Book Name" << "Author" << "Condition" << "Available" << "Price" << "Rent Price";
    booksTable->setHorizontalHeaderLabels(headers);
    booksTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    booksTable->setStyleSheet("QTableWidget { background-color: rgba(255, 255, 255, 200); border-radius: 5px; padding: 2px; }"
                              "QHeaderView::section { background-color: #333; color: white; padding: 4px; font-size: 11px; }");
    booksTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    booksTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    booksTable->setAlternatingRowColors(true);
    booksTable->verticalHeader()->setDefaultSectionSize(25);  // Reduced row height
    booksTable->setMinimumHeight(120);  // Reduced minimum height

    // Create buttons for main functions - compact layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(8);  // Reduced spacing

    // Create compact buttons
    recommendedBooksButton = new QPushButton("Recommended", this);
    recommendedBooksButton->setMinimumSize(90, 30);  // Reduced size
    recommendedBooksButton->setStyleSheet("QPushButton {"
                                          "background-color: #4CAF50;"
                                          "color: white;"
                                          "border-radius: 5px;"
                                          "font-size: 11px;"
                                          "font-weight: bold;"
                                          "padding: 3px;"
                                          "}"
                                          "QPushButton:hover {"
                                          "background-color: #45a049;"
                                          "}");

    viewBookButton = new QPushButton("View", this);
    viewBookButton->setMinimumSize(70, 30);  // Reduced size
    viewBookButton->setStyleSheet("QPushButton {"
                                  "background-color: #9C27B0;"
                                  "color: white;"
                                  "border-radius: 5px;"
                                  "font-size: 11px;"
                                  "font-weight: bold;"
                                  "padding: 3px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #8e24aa;"
                                  "}");

    // Add Buy button
    buyBookButton = new QPushButton("Buy", this);
    buyBookButton->setMinimumSize(70, 30);  // Matching existing buttons
    buyBookButton->setStyleSheet("QPushButton {"
                                 "background-color: #FF9800;"
                                 "color: white;"
                                 "border-radius: 5px;"
                                 "font-size: 11px;"
                                 "font-weight: bold;"
                                 "padding: 3px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #FB8C00;"
                                 "}");

    rentBookButton = new QPushButton("Rent", this);
    rentBookButton->setMinimumSize(70, 30);  // Reduced size
    rentBookButton->setStyleSheet("QPushButton {"
                                  "background-color: #007BFF;"
                                  "color: white;"
                                  "border-radius: 5px;"
                                  "font-size: 11px;"
                                  "font-weight: bold;"
                                  "padding: 3px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #0056b3;"
                                  "}");

    returnBookButton = new QPushButton("Return", this);
    returnBookButton->setMinimumSize(70, 30);  // Reduced size
    returnBookButton->setStyleSheet("QPushButton {"
                                    "background-color: #17a2b8;"
                                    "color: white;"
                                    "border-radius: 5px;"
                                    "font-size: 11px;"
                                    "font-weight: bold;"
                                    "padding: 3px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #138496;"
                                    "}");

    buttonLayout->addWidget(recommendedBooksButton);
    buttonLayout->addWidget(viewBookButton);
    buttonLayout->addWidget(buyBookButton);  // Add buy button to layout
    buttonLayout->addWidget(rentBookButton);
    buttonLayout->addWidget(returnBookButton);
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Add small spacer
    QSpacerItem *spacerItem = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

    // Create checkout section with compact layout
    QGroupBox *checkoutGroup = new QGroupBox("Checkout", this);
    checkoutGroup->setStyleSheet("QGroupBox { color: white; background-color: rgba(0, 0, 0, 120); border-radius: 5px; padding: 5px; font-size: 12px; font-weight: bold; }");

    QVBoxLayout *checkoutLayout = new QVBoxLayout(checkoutGroup);
    checkoutLayout->setSpacing(8);  // Reduced spacing
    checkoutLayout->setContentsMargins(10, 15, 10, 10);  // Reduced internal padding

    // Cart table - compact
    cartTable = new QTableWidget(this);
    cartTable->setColumnCount(3);
    QStringList cartHeaders;
    cartHeaders << "Book Name" << "Type" << "Price";
    cartTable->setHorizontalHeaderLabels(cartHeaders);
    cartTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    cartTable->setStyleSheet("QTableWidget { background-color: rgba(255, 255, 255, 200); border-radius: 5px; padding: 2px; }"
                             "QHeaderView::section { background-color: #333; color: white; padding: 3px; font-size: 11px; }");
    cartTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cartTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    cartTable->setAlternatingRowColors(true);
    cartTable->setMinimumHeight(80);  // Reduced height
    cartTable->verticalHeader()->setDefaultSectionSize(22);  // Reduced row height

    // Rental days section - compact
    QHBoxLayout *rentalLayout = new QHBoxLayout();
    rentalLayout->setSpacing(8);

    rentalDaysLabel = new QLabel("Rental Period (days):", this);
    rentalDaysLabel->setStyleSheet("color: white; font-size: 11px;");

    rentalDaysSpinBox = new QSpinBox(this);
    rentalDaysSpinBox->setMinimum(1);
    rentalDaysSpinBox->setMaximum(30);
    rentalDaysSpinBox->setValue(7);
    rentalDaysSpinBox->setStyleSheet("background-color: rgba(255, 255, 255, 200); border-radius: 3px; padding: 2px; font-size: 11px;");
    rentalDaysSpinBox->setMinimumHeight(22);
    rentalDaysSpinBox->setMinimumWidth(50);

    rentalLayout->addWidget(rentalDaysLabel);
    rentalLayout->addWidget(rentalDaysSpinBox);
    rentalLayout->addStretch();

    // Total price label - smaller
    totalPriceLabel = new QLabel("Total Price: $0.00", this);
    totalPriceLabel->setStyleSheet("color: white; font-size: 12px; font-weight: bold; padding: 2px;");
    totalPriceLabel->setAlignment(Qt::AlignRight);

    // Checkout button - smaller
    checkoutButton = new QPushButton("Checkout", this);
    checkoutButton->setMinimumSize(100, 30);  // Reduced size
    checkoutButton->setStyleSheet("QPushButton {"
                                  "background-color: #28a745;"
                                  "color: white;"
                                  "border-radius: 5px;"
                                  "font-size: 12px;"
                                  "font-weight: bold;"
                                  "padding: 3px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #218838;"
                                  "}");

    // Add widgets to checkout layout
    checkoutLayout->addWidget(cartTable);
    checkoutLayout->addLayout(rentalLayout);
    checkoutLayout->addWidget(totalPriceLabel);

    // Add checkout button centered
    QHBoxLayout *checkoutButtonLayout = new QHBoxLayout();
    checkoutButtonLayout->addStretch();
    checkoutButtonLayout->addWidget(checkoutButton);
    checkoutButtonLayout->addStretch();
    checkoutLayout->addLayout(checkoutButtonLayout);

    // Logout button - smaller
    logoutButton = new QPushButton("Logout", this);
    logoutButton->setMinimumSize(80, 25);  // Reduced size
    logoutButton->setStyleSheet("QPushButton {"
                                "background-color: #f44336;"
                                "color: white;"
                                "border-radius: 4px;"
                                "font-size: 11px;"
                                "font-weight: bold;"
                                "padding: 3px;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #d32f2f;"
                                "}");

    // Add widgets to main layout with reduced spacing
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(welcomeLabel);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(booksTable, 3);  // Give more relative space to book table
    mainLayout->addLayout(buttonLayout);
    mainLayout->addItem(spacerItem);
    mainLayout->addWidget(checkoutGroup, 2);  // Space for checkout section

    // Create layout for logout button to align it right with spacing
    QHBoxLayout *logoutLayout = new QHBoxLayout();
    logoutLayout->addStretch();
    logoutLayout->addWidget(logoutButton);
    mainLayout->addLayout(logoutLayout);

    // Add minimal spacing at the bottom
    mainLayout->addSpacing(5);

    // Connect signals and slots
    connect(searchButton, &QPushButton::clicked, this, &StudentDashboard::onSearchButtonClicked);
    connect(recommendedBooksButton, &QPushButton::clicked, this, &StudentDashboard::onRecommendedBooksButtonClicked);
    connect(viewBookButton, &QPushButton::clicked, this, &StudentDashboard::onViewBookButtonClicked);
    connect(buyBookButton, &QPushButton::clicked, this, &StudentDashboard::onBuyBookButtonClicked);  // Connect buy button
    connect(rentBookButton, &QPushButton::clicked, this, &StudentDashboard::onRentBookButtonClicked);
    connect(returnBookButton, &QPushButton::clicked, this, &StudentDashboard::onReturnBookButtonClicked);
    connect(checkoutButton, &QPushButton::clicked, this, &StudentDashboard::onCheckoutButtonClicked);
    connect(logoutButton, &QPushButton::clicked, this, &StudentDashboard::onLogoutButtonClicked);
    connect(rentalDaysSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &StudentDashboard::updateTotalPrice);

    // Connect to book repository changes
    connect(BookRepository::getInstance(), &BookRepository::bookAdded, this, &StudentDashboard::onBookAdded);
    connect(BookRepository::getInstance(), &BookRepository::booksChanged, this, &StudentDashboard::refreshBookTable);

    // Refresh the table with books from repository
    refreshBookTable();
}

StudentDashboard::~StudentDashboard()
{
}

void StudentDashboard::paintEvent(QPaintEvent *event)
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

void StudentDashboard::refreshBookTable()
{
    // Clear the table
    booksTable->setRowCount(0);

    // Fetch all books from the repository
    QVector<Book> books = BookRepository::getInstance()->getAllBooks();

    // Add each book to the table
    for (const Book &book : books) {
        // Get price and rent price from the book object
        double price = book.price;
        double rentPrice = book.rentPrice;

        addBookToTable(book.name, book.author, book.condition, book.status == "Available", price, rentPrice);
    }
}

void StudentDashboard::onBookAdded(const Book &book)
{
    // Add newly added book to table with price information
    addBookToTable(book.name, book.author, book.condition, book.status == "Available", book.price, book.rentPrice);
}

void StudentDashboard::onSearchButtonClicked()
{
    QString searchText = searchEdit->text();

    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Search", "Please enter a search term.");
        return;
    }

    // Filter the table based on search text
    for (int i = 0; i < booksTable->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < booksTable->columnCount(); ++j) {
            QTableWidgetItem *item = booksTable->item(i, j);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        booksTable->setRowHidden(i, !match);
    }
}

void StudentDashboard::onRecommendedBooksButtonClicked()
{
    // Create and show the recommended books window
    bookExplorer = new BookExplorer(this, false, true);
    bookExplorer->show();
}

void StudentDashboard::onViewBookButtonClicked()
{
    // Get the selected row
    QModelIndexList selectedIndexes = booksTable->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "View Book", "Please select a book to view.");
        return;
    }

    int row = selectedIndexes.first().row();
    QString bookName = booksTable->item(row, 0)->text();
    QString available = booksTable->item(row, 3)->text();

    if (available == "No") {
        QMessageBox::warning(this, "View Book", "This book is not available for viewing.");
        return;
    }

    // Get PDF path from book repository
    QString pdfPath = BookRepository::getInstance()->getPdfPath(bookName);
    if (!pdfPath.isEmpty()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(pdfPath));
    } else {
        QMessageBox::information(this, "View Book", "No PDF available for this book.");
    }
}

// New method for buying books
void StudentDashboard::onBuyBookButtonClicked()
{
    // Get the selected row
    QModelIndexList selectedIndexes = booksTable->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Buy Book", "Please select a book to buy.");
        return;
    }

    int row = selectedIndexes.first().row();
    QString bookName = booksTable->item(row, 0)->text();
    QString available = booksTable->item(row, 3)->text();

    if (available == "No") {
        QMessageBox::warning(this, "Buy Book", "This book is not available for purchase.");
        return;
    }

    // Get purchase price
    QString priceStr = booksTable->item(row, 4)->text();
    double price = priceStr.remove("$").toDouble();

    // Add to cart items (purchase items)
    cartItems.append(qMakePair(bookName, price));

    // Add to cart table
    int cartRow = cartTable->rowCount();
    cartTable->insertRow(cartRow);

    QTableWidgetItem *nameItem = new QTableWidgetItem(bookName);
    QTableWidgetItem *typeItem = new QTableWidgetItem("Purchase");
    QTableWidgetItem *priceItem = new QTableWidgetItem(QString("$%1").arg(price, 0, 'f', 2));

    // Set small font for cart items
    QFont cartFont = nameItem->font();
    cartFont.setPointSize(9);

    nameItem->setFont(cartFont);
    typeItem->setFont(cartFont);
    priceItem->setFont(cartFont);

    cartTable->setItem(cartRow, 0, nameItem);
    cartTable->setItem(cartRow, 1, typeItem);
    cartTable->setItem(cartRow, 2, priceItem);

    // Update total price
    totalPrice += price;
    totalPriceLabel->setText(QString("Total Price: $%1").arg(totalPrice, 0, 'f', 2));

    QMessageBox::information(this, "Buy Book", QString("Book '%1' has been added to your cart for purchase.").arg(bookName));
}

void StudentDashboard::onReturnBookButtonClicked()
{
    // Show a dialog to enter book name to return
    QString bookName = QInputDialog::getText(this, "Return Book", "Enter the name of the book you want to return:");

    if (bookName.isEmpty()) {
        return;
    }

    // Check if book exists in repository
    Book book = BookRepository::getInstance()->getBook(bookName);
    if (book.name.isEmpty()) {
        QMessageBox::warning(this, "Return Book", "Book not found in the library.");
        return;
    }

    // Check if book is marked as rented
    if (book.status == "Available") {
        QMessageBox::warning(this, "Return Book", "This book is not currently rented out.");
        return;
    }

    // Calculate days overdue
    QDate dueDate = QDate::fromString(book.dueDate, "yyyy-MM-dd");
    QDate currentDate = QDate::currentDate();
    int daysOverdue = 0;

    if (currentDate > dueDate) {
        daysOverdue = dueDate.daysTo(currentDate);
    }

    double penalty = 0.0;
    if (daysOverdue > 0) {
        // Apply penalty - $1 per day overdue
        penalty = daysOverdue * 1.0;

        QMessageBox::warning(this, "Return Book",
                             QString("The book is %1 days overdue. A penalty of $%2 will be applied.")
                                 .arg(daysOverdue)
                                 .arg(penalty, 0, 'f', 2));
    }

    // Update book status in repository
    BookRepository::getInstance()->updateBookStatus(bookName, "Available");
    BookRepository::getInstance()->updateBookDueDate(bookName, ""); // Clear due date

    if (penalty > 0) {
        // Add penalty to cart
        int cartRow = cartTable->rowCount();
        cartTable->insertRow(cartRow);

        QTableWidgetItem *nameItem = new QTableWidgetItem(bookName + " (Penalty)");
        QTableWidgetItem *typeItem = new QTableWidgetItem("Penalty");
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString("$%1").arg(penalty, 0, 'f', 2));

        // Set small font for cart items
        QFont cartFont = nameItem->font();
        cartFont.setPointSize(9);

        nameItem->setFont(cartFont);
        typeItem->setFont(cartFont);
        priceItem->setFont(cartFont);

        cartTable->setItem(cartRow, 0, nameItem);
        cartTable->setItem(cartRow, 1, typeItem);
        cartTable->setItem(cartRow, 2, priceItem);

        // Update total price
        totalPrice += penalty;
        totalPriceLabel->setText(QString("Total Price: $%1").arg(totalPrice, 0, 'f', 2));
    }

    QMessageBox::information(this, "Return Book",
                             QString("Book '%1' has been successfully returned.").arg(bookName));

    // Refresh book table to reflect the changes
    refreshBookTable();
}

void StudentDashboard::onCheckoutButtonClicked()
{
    if (cartTable->rowCount() == 0) {
        QMessageBox::warning(this, "Checkout", "Your cart is empty.");
        return;
    }

    // Calculate final price
    updateTotalPrice();

    // Ask for confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Checkout Confirmation",
                                  QString("Total amount: $%1\nProceed with checkout?").arg(totalPrice, 0, 'f', 2),
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Process purchased books
        for (const auto &item : cartItems) {
            QString bookName = item.first;
            BookRepository::getInstance()->updateBookStatus(bookName, "Sold");
        }

        // Process rented books
        int rentalDays = rentalDaysSpinBox->value();
        QDate dueDate = QDate::currentDate().addDays(rentalDays);

        for (const auto &item : rentedBooks) {
            QString bookName = item.first;
            BookRepository::getInstance()->updateBookStatus(bookName, "Rented");
            BookRepository::getInstance()->updateBookDueDate(bookName, dueDate.toString("yyyy-MM-dd"));
        }

        // Clear cart
        cartTable->setRowCount(0);
        cartItems.clear();
        rentedBooks.clear();
        totalPrice = 0.0;
        updateTotalPrice();

        QMessageBox::information(this, "Checkout Complete",
                                 "Your transaction has been completed successfully!");

        // Refresh book table to show updated availability
        refreshBookTable();
    }
}

void StudentDashboard::updateTotalPrice()
{
    totalPrice = 0.0;

    // Calculate purchase prices
    for (const auto &item : cartItems) {
        totalPrice += item.second;  // Add the price of each purchased book
    }

    // Calculate rental prices with rental days factor
    int rentalDays = rentalDaysSpinBox->value();
    for (const auto &item : rentedBooks) {
        // Daily rental price multiplied by rental days
        totalPrice += item.second * rentalDays;
    }

    // Update the label
    totalPriceLabel->setText(QString("Total Price: $%1").arg(totalPrice, 0, 'f', 2));
}

void StudentDashboard::onLogoutButtonClicked()
{
    // Hide this window and show the main window
    this->hide();
    this->parentWidget()->show();
}

void StudentDashboard::addBookToTable(const QString &name, const QString &author, const QString &condition, bool available, double price, double rentPrice)
{
    int row = booksTable->rowCount();
    booksTable->insertRow(row);

    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *authorItem = new QTableWidgetItem(author);
    QTableWidgetItem *conditionItem = new QTableWidgetItem(condition);
    QTableWidgetItem *availableItem = new QTableWidgetItem(available ? "Yes" : "No");
    QTableWidgetItem *priceItem = new QTableWidgetItem(QString("$%1").arg(price, 0, 'f', 2));
    QTableWidgetItem *rentPriceItem = new QTableWidgetItem(QString("$%1").arg(rentPrice, 0, 'f', 2));

    // Smaller font size for table items
    QFont itemFont = nameItem->font();
    itemFont.setPointSize(9);

    nameItem->setFont(itemFont);
    authorItem->setFont(itemFont);
    conditionItem->setFont(itemFont);
    availableItem->setFont(itemFont);
    priceItem->setFont(itemFont);
    rentPriceItem->setFont(itemFont);

    booksTable->setItem(row, 0, nameItem);
    booksTable->setItem(row, 1, authorItem);
    booksTable->setItem(row, 2, conditionItem);
    booksTable->setItem(row, 3, availableItem);
    booksTable->setItem(row, 4, priceItem);
    booksTable->setItem(row, 5, rentPriceItem);
}

void StudentDashboard::onRentBookButtonClicked()
{
    // Get the selected row
    QModelIndexList selectedIndexes = booksTable->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Rent Book", "Please select a book to rent.");
        return;
    }

    int row = selectedIndexes.first().row();
    QString bookName = booksTable->item(row, 0)->text();
    QString available = booksTable->item(row, 3)->text();

    if (available == "No") {
        QMessageBox::warning(this, "Rent Book", "This book is not available for rent.");
        return;
    }

    // Get rent price
    QString rentPriceStr = booksTable->item(row, 5)->text();
    double rentPrice = rentPriceStr.remove("$").toDouble();

    // Add to cart
    rentedBooks.append(qMakePair(bookName, rentPrice));

    // Add to cart table
    int cartRow = cartTable->rowCount();
    cartTable->insertRow(cartRow);

    QTableWidgetItem *nameItem = new QTableWidgetItem(bookName);
    QTableWidgetItem *typeItem = new QTableWidgetItem("Rent");
    QTableWidgetItem *priceItem = new QTableWidgetItem(QString("$%1/day").arg(rentPrice, 0, 'f', 2));

    // Set small font for cart items
    QFont cartFont = nameItem->font();
    cartFont.setPointSize(9);

    nameItem->setFont(cartFont);
    typeItem->setFont(cartFont);
    priceItem->setFont(cartFont);

    cartTable->setItem(cartRow, 0, nameItem);
    cartTable->setItem(cartRow, 1, typeItem);
    cartTable->setItem(cartRow, 2, priceItem);

    // Update total price
    updateTotalPrice();

    QMessageBox::information(this, "Rent Book", QString("Book '%1' has been added to your cart for renting.").arg(bookName));
}
