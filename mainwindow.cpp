#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow()
{
        createActions();
        createMenus();
        (void)statusBar();
        setWindowTitle(tr("File manager"));
        toogle = false;

        // all directories
        pathLabel = new QLabel(tr("Path  :"));
        directoryComboBox = new QComboBox;
        directoryComboBox->setEditable(true);
        directoryComboBox->addItem(QDir::currentPath());
        directoryComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

        // basis for renaming
        renameLabel = new QLabel(tr("Name:"));
        renameComboBox = new QComboBox;
        renameComboBox->setEditable(true);
        renameComboBox->addItem(tr("Name for files"));
        renameComboBox->setFixedHeight(23);
        renameComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

        // method of sorting
        sortComboBox = new QComboBox;
        sortComboBox->addItem(tr("Name"));		// 0
        sortComboBox->addItem(tr("Time"));		// 1
        sortComboBox->addItem(tr("Size"));		// 2
        sortComboBox->addItem(tr("Unsorted"));	// 3
        sortComboBox->addItem(tr("Type"));		// 4
        sortLabel = new QLabel(tr("&Sort  :"));
        sortLabel->setBuddy(sortComboBox);

        // starter from number
        numberStarter = new QSpinBox;
        numberStarter->setRange(1, 10000000);
        numberStarter->setFixedWidth(75);
        numberLabel = new QLabel(tr("&Starter:"));
        numberLabel->setBuddy(numberStarter);

        // sort by ascending sorting or descending sorting
        descendingSort  = new QCheckBox(tr("&descending sort"));
        descendingLabel = new QLabel(tr("&Sort as:"));
        descendingLabel->setBuddy(descendingSort);

        // buttons
        renameButton = new QPushButton(tr("&Rename"));
        renameButton->setDefault(true);
        quitButton = new QPushButton(tr("&Quit"));
        quitButton->setAutoDefault(false);
        browseButton = new QPushButton(tr("&Browse"));
        browseButton->setAutoDefault(false);
        moreButton = new QPushButton(tr("&More"));
        //moreButton->setAutoDefault(false);
        moreButton->setCheckable(true);

        // unite three buttons
        buttonBox = new QDialogButtonBox;
        buttonBox->addButton(renameButton, QDialogButtonBox::ActionRole);
        buttonBox->addButton(quitButton,   QDialogButtonBox::RejectRole);
        buttonBox->addButton(moreButton,   QDialogButtonBox::ApplyRole);

        // data output
        lastNumberAfterRename = new QLineEdit;
        nameBeforeRename = new QTextEdit;
        nameAfterRename  = new QTextEdit;

        lastNumberLabel = new QLabel(tr("The last renaming file:"));
        beforeLabel = new QLabel(tr("Before:"));
        afterLabel = new QLabel(tr("After:"));

        /**************************************************************************
                –аскладываем все по местам
        **************************************************************************/

        // create the first horizontal layout
        QHBoxLayout *horizontalLayoutFirst = new QHBoxLayout;
        horizontalLayoutFirst->addWidget(pathLabel);
        horizontalLayoutFirst->addWidget(directoryComboBox);
        horizontalLayoutFirst->addWidget(browseButton);

        // create the second horizontal layout
        QHBoxLayout *horizontalLayoutSecond = new QHBoxLayout;
        horizontalLayoutSecond->addWidget(renameLabel);
        horizontalLayoutSecond->addWidget(renameComboBox);

        // create the third horizontal layout
        QHBoxLayout *horizontalLayoutThird = new QHBoxLayout;
        horizontalLayoutThird->addWidget(sortLabel);
        horizontalLayoutThird->addWidget(sortComboBox);
        horizontalLayoutThird->addWidget(numberLabel);
        horizontalLayoutThird->addWidget(numberStarter);
        horizontalLayoutThird->addWidget(descendingLabel);
        horizontalLayoutThird->addWidget(descendingSort);
        horizontalLayoutThird->addStretch();

        // create the fifth horizontal layout
        QHBoxLayout *horizontalLayoutFifth = new QHBoxLayout;
        horizontalLayoutFifth->addStretch();
        horizontalLayoutFifth->addWidget(lastNumberLabel);
        horizontalLayoutFifth->addStretch();

        // create the sixth horizontal layout
        QHBoxLayout *horizontalLayoutSixth = new QHBoxLayout;
        horizontalLayoutSixth->addWidget(lastNumberAfterRename);

        // create the seventh horizontal layout
        QHBoxLayout *horizontalLayoutSeventh = new QHBoxLayout;
        horizontalLayoutSeventh->addStretch();
        horizontalLayoutSeventh->addWidget(beforeLabel);
        horizontalLayoutSeventh->addStretch();
        horizontalLayoutSeventh->addStretch();
        horizontalLayoutSeventh->addWidget(afterLabel);
        horizontalLayoutSeventh->addStretch();

        // create the eight horizontal layout
        QHBoxLayout *horizontalLayoutEight = new QHBoxLayout;
        horizontalLayoutEight->addWidget(nameBeforeRename);
        horizontalLayoutEight->addWidget(nameAfterRename);

        // create the first vertical layout
        QVBoxLayout *verticalLayoutFirst = new QVBoxLayout;
        verticalLayoutFirst->addLayout(horizontalLayoutFirst);
        verticalLayoutFirst->addLayout(horizontalLayoutSecond);
        verticalLayoutFirst->addLayout(horizontalLayoutThird);
        verticalLayoutFirst->addWidget(buttonBox);

        // create the second vertical layout
        QVBoxLayout *verticalLayoutSecond = new QVBoxLayout;
        verticalLayoutSecond->addLayout(horizontalLayoutFifth);
        verticalLayoutSecond->addLayout(horizontalLayoutSixth);
        verticalLayoutSecond->addLayout(horizontalLayoutSeventh);
        verticalLayoutSecond->addLayout(horizontalLayoutEight);

        hideBox = new QGroupBox;
        hideBox->setLayout(verticalLayoutSecond);
        hideBox->hide();

        // create the vertical layer
        mainLayout = new QGridLayout;
        mainLayout->addLayout(verticalLayoutFirst, 0, 0, Qt::AlignTop);
        mainLayout->addWidget(hideBox, 1, 0);
        //mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

        widget = new QWidget;
        widget->setLayout(mainLayout);
        QMainWindow::setMinimumWidth(400);
        QMainWindow::setMaximumHeight(140);
        setCentralWidget(widget);

        // Buttons
        connect(renameButton, SIGNAL(clicked()), this, SLOT(rename()));
        connect(quitButton,   SIGNAL(clicked()), this, SLOT(close()));
        connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));
        connect(moreButton,   SIGNAL(clicked()), this, SLOT(more()));
}
void MainWindow::more()
{
        mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
        setMinimumSize(0, 0);
        // show date output
        if(!toogle)
        {
                QMainWindow::setMinimumWidth(400);
                QMainWindow::setMaximumHeight(1200);
                hideBox->show();
                resize(QMainWindow::width(), 500);
                toogle = true;
        }
        // hide date output
        else
        {
                hideBox->hide();
                resize(QMainWindow::width(), 140);
                QMainWindow::setMinimumWidth(400);
                QMainWindow::setMaximumHeight(140);
                toogle = false;
        }
        mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
}

void MainWindow::browse()
{
        directoryName = QFileDialog::getExistingDirectory(this,
                tr("Selest a need directory"), lastDirectory);
        // add to the history list
        if (!directoryName.isEmpty())
        {
                directoryComboBox->addItem(directoryName);
                directoryComboBox->setCurrentIndex(directoryComboBox->currentIndex() + 1);
        }
        lastDirectory = QFileInfo(directoryName).absoluteFilePath();
}

void MainWindow::about()
{
        QMessageBox::about(this, tr("About File manager"),
            tr("The <b>File manager</b> can rename all image files in your directory."));
}

void MainWindow::rename()
{
        myCoolRename(this->sortComboBox->currentIndex());
}

void MainWindow::myCoolRename(int sortFlag)
{
        // clear of data output
        nameBeforeRename->clear();
        nameAfterRename ->clear();
        // имеетс€: путь к директории - directoryName, им€ файла - newName, стартер - start
        QString newName = renameComboBox->currentText();
        if(!renameComboBox->currentText().isEmpty())
        {
                renameComboBox->addItem(renameComboBox->currentText());
                renameComboBox->setCurrentIndex(renameComboBox->currentIndex() + 1);
        }
        // for the converting from int to string
        QString str;
        // return way to directory
        QDir dir(directoryComboBox->currentText());
        // contain list from QString
        QStringList filters;
        // create array with required expansion for the changing

        filters += "*.jpg";
        filters += "*.bmp";
        filters += "*.png";
        filters += "*.jpeg";
        filters += "*.ppm";
        filters += "*.tiff";
        filters += "*.xbm";
        filters += "*.xpm";

        int i = numberStarter->value();
        QStringList oldListFiles;
        QStringList newListFiles;
        // create array of files by necessary condition
        switch(sortFlag)
        {
        case 0: // Name
                oldListFiles = dir.entryList(filters, QDir::Files, QDir::Name);
                oldListFiles = sortStringList(oldListFiles);
                break;
        case 1: // Time
                oldListFiles = dir.entryList(filters, QDir::Files, QDir::Time);
                break;
        case 2: // Size
                oldListFiles = dir.entryList(filters, QDir::Files, QDir::Size);
                break;
        case 3: // Unsort
                oldListFiles = dir.entryList(filters, QDir::Files, QDir::Unsorted);
                break;
        case 4: // Type
                oldListFiles = dir.entryList(filters, QDir::Files, QDir::Type);
                break;
        }
        // intermediate renaming
        foreach(QString file, oldListFiles)
        {
                // делаетс€ из-за глюка Qt4 с вычленением регул€рных выражений
                QString myCompleteSuffix = (QString)QFileInfo(dir, file).completeSuffix();
                // конвертим к регул€рным выражени€м
                myCompleteSuffix = convertToMyCompleteSuffix(myCompleteSuffix);

                nameBeforeRename->insertPlainText
                        ((QString)("Rename of " + str.setNum(i) + ": \t" + QFileInfo(dir, file).fileName() + '\r' + '\n'));

                newListFiles +=
                        (QString) (newName + str.setNum(i) + "'-!#$%&(),[]^_`{}." + myCompleteSuffix);
                // intermediate renaming
                dir.rename(QFileInfo(dir, file).fileName(),
                        (QString) (newName + str.setNum(i) + "'-!#$%&(),[]^_`{}." + myCompleteSuffix));

                i++;
        }
        // return to datum value
        i = numberStarter->value();
        // real renaming
        foreach(QString file, newListFiles)
        {
                QString myCompleteSuffix = (QString)QFileInfo(dir, file).completeSuffix();
                myCompleteSuffix = convertToMyCompleteSuffix(myCompleteSuffix);

                nameAfterRename ->insertPlainText
                        ((QString)("Rename of " + str.setNum(i) + ": \t" + newName + str.setNum(i)
                                   + "." + myCompleteSuffix + '\r' + '\n'));
                // renaming
                dir.rename(QFileInfo(dir, file).fileName(),
                         (QString) (newName + str.setNum(i) + "." + myCompleteSuffix));

                lastNumberAfterRename->setText
                        ((QString) (newName + str.setNum(i) + "." + myCompleteSuffix));
                i++;
        }
}

void MainWindow::createActions()
{
        // the first menu
    openAct = new QAction(tr("&Set directory..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(browse()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

        // the second menu
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    // the first menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    // установка директории
    fileMenu->addAction(openAct);
    // разделитель
    fileMenu->addSeparator();
    // exit
    fileMenu->addAction(exitAct);
    // the second menu
    helpMenu = menuBar()->addMenu(tr("&Help"));
    // about FileManager
    helpMenu->addAction(aboutAct);
    // about Qt4
    helpMenu->addAction(aboutQtAct);
}
// convert to regular expression
QString MainWindow::convertToMyCompleteSuffix(QString toMyCompleteSuffix)
{
        if (    toMyCompleteSuffix == (QString)"jpg" || toMyCompleteSuffix == (QString)"bmp"  ||
                toMyCompleteSuffix == (QString)"png" || toMyCompleteSuffix == (QString)"jpeg" ||
                toMyCompleteSuffix == (QString)"ppm" || toMyCompleteSuffix == (QString)"tiff" ||
                toMyCompleteSuffix == (QString)"xbm" || toMyCompleteSuffix == (QString)"xpm")
        {
                return toMyCompleteSuffix;
        }
        else
        {
                // don't touch!!! if your like your hands
                std::string str = toMyCompleteSuffix.toStdString();
                char *charFullSuffix = const_cast<char *> (str.c_str());
                QString afterPoint;
                while(*charFullSuffix)
                {
                        afterPoint += (QString)*charFullSuffix;
                        if(tolower((int)*charFullSuffix) == '.')
                        {
                                afterPoint.clear();
                        }
                        *charFullSuffix++;
                }
                return afterPoint;
        }
}
// detect the method of sorting
QStringList MainWindow::sortStringList(QStringList stringList)
{
        if(stringList.count() <= 2)
        {
                bubbleSort(stringList, descendingSort->isChecked());
        }
        else if(stringList.count() >= 3)
        {
                quickSort(stringList, 0, stringList.count() - 1, descendingSort->isChecked());
        }
        return stringList;
}
// bubble sort
void bubbleSort(QStringList &stringList, bool up_d)
{
        QString temp;
        for(int a = 1 ; a < stringList.count() ; a++)
        {
                for(int b = stringList.count() - 1 ; b >= a; b--)
                {
                        // по возрастанию - 0
                        if(!up_d)
                        {
                                if(stringList[b-1].toStdString() > stringList[b].toStdString())
                                {
                                        temp = stringList[b-1];
                                        stringList[b-1] = stringList[b];
                                        stringList[b] = temp;
                                }
                        }
                        // по убыванию - 1
                        else if(up_d)
                        {
                                if(stringList[b-1].toStdString() < stringList[b].toStdString())
                                {
                                        temp = stringList[b-1];
                                        stringList[b-1] = stringList[b];
                                        stringList[b] = temp;
                                }
                        }
                }
        }
}
// quick sort
void quickSort (QStringList &stringList, int left, int right, bool up_d)
{
        int i; // leader
        int j; // end
        QString x; // half of massive
        QString y; // temp-variable
        i = left;
        j = right;
        x = stringList[(left + right) / 2];
        do
        {
                //  ascending sort - 0
                if (!up_d)
                {
                        while (stringList[i].toStdString() < x.toStdString())
                        {
                                i++;
                        }
                        while (stringList[j].toStdString() > x.toStdString())
                        {
                                j--;
                        }
                }
                // descending sort - 1
                else if(up_d)
                {
                        while (stringList[i].toStdString() > x.toStdString())
                        {
                                i++;
                        }
                        while (stringList[j].toStdString() < x.toStdString())
                        {
                                j--;
                        }
                }
                if(i <= j)
                {
                        y = stringList[i];
                        stringList[i] = stringList[j];
                        stringList[j] = y;
                        i++;
                        j--;
                }
        }
        while (i <= j);
        if  (left < j) quickSort(stringList, left, j, up_d);
        if (right > i) quickSort(stringList, i, right, up_d);
}
// operator <
bool operator< (std::string qstr1, std::string qstr2)
{
        // if (str2 > str1) return true, else return false
        return qstr2 > qstr1 ? true : false;
}
// operator >
bool operator> (std::string qstr1, std::string qstr2)
{
        // convert to char frim string
        const char *charStr1 = qstr1.c_str();
        const char *charStr2 = qstr2.c_str();

        // controllers of numbers
        bool numberControlOne = false;
        bool numberControlTwo = false;

        int real = 0;

        while(*charStr1 || *charStr2)
        {
                if (*charStr1 == '0' || *charStr1 == '1' || *charStr1 == '2' || *charStr1 == '3' || *charStr1 == '4' ||
                    *charStr1 == '5' || *charStr1 == '6' || *charStr1 == '7' || *charStr1 == '8' || *charStr1 == '9')
                {
                        numberControlOne = true;
                }

                if (*charStr2 == '0' || *charStr2 == '1' || *charStr2 == '2' || *charStr2 == '3' || *charStr2 == '4' ||
                    *charStr2 == '5' || *charStr2 == '6' || *charStr2 == '7' || *charStr2 == '8' || *charStr2 == '9')
                {
                        numberControlTwo = true;
                }

                if(numberControlOne && numberControlTwo)
                {
                        return getNumber(charStr1, 0) > getNumber(charStr2, 0) ? true : false;
                }

                if(*charStr1 != *charStr2)
                {
                        return compareChars(charStr1, charStr2, real) ? true : false;
                }

                *charStr1++;
                *charStr2++;
                real++;
        }
        return 0;
}
// get numeral
int getNumber(const char *ch, int sum)
{
        int number;
        const char *massive = "0123456789";
        bool isNumber = false;

        // извлечение из строки цифры

        for(int i = 0; i < 10 ; i++)
        {
                if(massive[i] == *ch)
                {
                        number = i;
                        isNumber = true;
                        break;
                }
        }

        // если следующий элемент не цифра
        if(!isNumber)
        {
                return sum;
        }
        // adding
        sum = sum*10 + number;
        // next symbol
        *ch++;
        // если кончилась строка
        if(*ch == '\0')
        {
                return sum;
        }
        // recursion
        getNumber(ch, sum);
}
// compare two symbols
bool compareChars(const char *ch1, const char *ch2, int counterNumber)
{
        // распологать символы в таком пор€дке
        const char *order = ".01234567890'- !#$%&(),[]^_`{}~+ABCDEFGHIJKLMNOPQRSTUVWXYZєјЅ¬√ƒ≈∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя";
        // почему будем сравнивать
        int orderNumberOne = 0;
        int orderNumberTwo = 0;
        // контроллеры поиска
        bool controlOrderNumberOne = false;
        bool controlOrderNumberTwo = false;

        int length =  strlen(order);
        // нахождение символов
        for(int i = 0; i < length ; i++)
        {
                if(tolower((int)*ch1) == tolower((int)order[i]))
                {
                        orderNumberOne = i;
                        controlOrderNumberOne = true;
                }
                if(tolower((int)*ch2) == tolower((int)order[i]))
                {
                        orderNumberTwo = i;
                        controlOrderNumberOne = true;
                }
                if(controlOrderNumberOne && controlOrderNumberTwo)
                {
                        break;
                }
        }

        // выверт винды, сцуко
        if ((orderNumberOne == 13 && strlen(ch1) != 1 && counterNumber == 0 && orderNumberTwo < 32) ||
                (orderNumberTwo == 13 && strlen(ch2) != 1 && counterNumber == 0 && orderNumberOne < 32))
        {
                return orderNumberOne == 13 ? true : false;
        }
        return orderNumberOne > orderNumberTwo ? true : false;
}
