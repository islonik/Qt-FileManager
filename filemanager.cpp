#include <QtGui>
#include "filemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
	//createActions();
    //createMenus();
    //(void)statusBar();
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
		
	/**************************************************************************
		Раскладываем все по местам
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

	// data output
	lastNumberAfterRename = new QLineEdit;
	nameBeforeRename = new QTextEdit;
	nameAfterRename  = new QTextEdit;

	lastNumberLabel = new QLabel(tr("The last renaming file:"));
	beforeLabel = new QLabel(tr("Before:"));
	afterLabel = new QLabel(tr("After:"));

	/***********************************************************
		Top secret
	***********************************************************/

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

	// create the groupbox
	hideBox = new QGroupBox;
	hideBox->setLayout(verticalLayoutSecond);
	hideBox->hide();

	// create the main layer
    mainLayout = new QGridLayout;
    mainLayout->addLayout(verticalLayoutFirst, 0, 0);
	mainLayout->addWidget(hideBox, 1, 0);
	mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(mainLayout);
	//widget = new QWidget;
    //widget->setLayout(mainLayout);
	//setCentralWidget(widget);

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
	
	if(!toogle)
	{
		/*QSize oldSizeHint = hideBox->sizeHint() + QSize(spacing, spacing);
		QSize newSizeHint = hideBox->sizeHint() + QSize(spacing, spacing);
		resize(size() + QSize(-oldSizeHint.width(), -newSizeHint.height()));*/
		hideBox->show();
		toogle = true;
	}
	else
	{
		int spacing = mainLayout->spacing();
		//QSize oldSizeHint = hideBox->sizeHint() + QSize(spacing, spacing);
		QSize newSizeHint = hideBox->sizeHint() + QSize(spacing, spacing);
		hideBox->hide();
		//resize(size() + QSize(-oldSizeHint.width(), -newSizeHint.height()));
		resize(size() + QSize(0, -newSizeHint.height()));
		toogle = false;
	}
	mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
}

void MainWindow::browse()
{
	directoryName = QFileDialog::getExistingDirectory(this,
		tr("Selest a need directory"), lastDirectory);
	// добавляем в список
	if (!directoryName.isEmpty()) 
	{
		directoryComboBox->addItem(directoryName);
		directoryComboBox->setCurrentIndex(directoryComboBox->currentIndex() + 1);
    }
	lastDirectory = QFileInfo(directoryName).absoluteFilePath();
}
/*
void MainWindow::about()
{
	QMessageBox::about(this, tr("About File manager"),
            tr("The <b>File manager</b> can rename all image files in your directory."));
}
*/
void MainWindow::rename()
{
	myCoolRename(this->sortComboBox->currentIndex());
}

void MainWindow::myCoolRename(int sortFlag)
{
	// clear of data output
	nameBeforeRename->clear();
	nameAfterRename ->clear();
	// имеется: путь к директории - directoryName, имя файла - newName, стартер - start
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
	foreach(QByteArray format, QImageReader::supportedImageFormats())
	{
		filters += "*." + format;
	}

	int i = numberStarter->value();
	QStringList oldListFiles;
	QStringList newListFiles;
	// create array of files by necessary condition
	switch(sortFlag)
	{
	case 0: // Name
		oldListFiles = dir.entryList(filters, QDir::Filter::Files, QDir::SortFlag::Name);
		oldListFiles = sortStringList(oldListFiles);
		break;
	case 1: // Time
		oldListFiles = dir.entryList(filters, QDir::Filter::Files, QDir::SortFlag::Time);
		break;
	case 2: // Size
		oldListFiles = dir.entryList(filters, QDir::Filter::Files, QDir::SortFlag::Size);
		break;
	case 3: // Unsort
		oldListFiles = dir.entryList(filters, QDir::Filter::Files, QDir::SortFlag::Unsorted);
		break;
	case 4: // Type
		oldListFiles = dir.entryList(filters, QDir::Filter::Files, QDir::SortFlag::Type);
		break;
	}
	// intermediate renaming
	foreach(QString file, oldListFiles)
	{
		// делается из-за глюка Qt4 с вычленением регулярных выражений
		QString myCompleteSuffix = (QString)QFileInfo(dir, file).completeSuffix();
		// конвертим к регулярным выражениям
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
										+ "." +	myCompleteSuffix + '\r' + '\n'));
		// renaming
		dir.rename(QFileInfo(dir, file).fileName(),
			(QString) (newName + str.setNum(i) + "." +	myCompleteSuffix));

		lastNumberAfterRename->setText
			((QString) (newName + str.setNum(i) + "." +	myCompleteSuffix));
		i++;
	}
}
/*
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
}*/
// convert to regular expression
QString MainWindow::convertToMyCompleteSuffix(QString toMyCompleteSuffix)
{
	if (toMyCompleteSuffix == (QString)"jpg" || toMyCompleteSuffix == (QString)"bmp"  ||
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
	const char *charTemp1 = qstr1.c_str();
	const char *charTemp2 = qstr2.c_str();

	// controllers of numbers
	bool numberControlOne = false;
	bool numberControlTwo = false;

	int real = 0;
	
	const char *massive = "0123456789";

	while(*charTemp1 || *charTemp2)
	{
		if (*charTemp1 == '0' || *charTemp1 == '1' || *charTemp1 == '2' || *charTemp1 == '3' || *charTemp1 == '4' ||
			*charTemp1 == '5' || *charTemp1 == '6' || *charTemp1 == '7' || *charTemp1 == '8' || *charTemp1 == '9')
		{
			numberControlOne = true;
		}
		
		if (*charTemp2 == '0' || *charTemp2 == '1' || *charTemp2 == '2' || *charTemp2 == '3' || *charTemp2 == '4' ||
			*charTemp2 == '5' || *charTemp2 == '6' || *charTemp2 == '7' || *charTemp2 == '8' || *charTemp2 == '9')
		{
			numberControlTwo = true;
		}

		if(numberControlOne && numberControlTwo)
		{
			return stringNumber(charTemp1, 0) >	stringNumber(charTemp2, 0) ? true : false;
		}


		if(*charTemp1 != *charTemp2)
		{
			return compareChars(charTemp1, charTemp2, real) ? true : false;
			
			/*for(int i = 0; i < 10; i++)
			{
				if(massive[i] == *charTemp1)
				{
					numberControlOne = true;
				}
				if(massive[i] == *charTemp2)
				{
					numberControlTwo = true;
				}
				// оба символа - цифры
				if(numberControlOne && numberControlTwo)
				{
					if((*charTemp1 == '0' || *charTemp2 == '0') && real != 0)
					{
						*charTemp1--;
						*charTemp2--;
						return convertCharacters(charTemp1, charTemp2, 0, real) ? true : false;
					}
					else
					{
						return stringNumber(charTemp1, 0) >	stringNumber(charTemp2, 0) ? true : false; 
					}
				}
				// одна цифра
				else if((numberControlOne || numberControlTwo) && i == 9)
				{
					*charTemp1--;
					*charTemp2--;
					return convertCharacters(charTemp1, charTemp2, 1, real) ? true : false;
				}
				// нет цифр
				else if((!numberControlOne && !numberControlTwo) && i == 9)
				{
					//return detectChar(charTemp1, real) > detectChar(charTemp2, real) ? true : false;
					return compareChars(charTemp1, charTemp2, real) ? true : false; 
				}
			}*/
		}
		
		*charTemp1++;
		*charTemp2++;
		real++;
	}
}
// converting to compare numerals or symbols
bool convertCharacters(const char *ch1, const char *ch2, bool flag, int counterNumber)
{
	int numberOne = NULL;
	int numberTwo = NULL;
	const char *massive = "0123456789";
	bool controlCh1 = false;
	bool controlCh2 = false;
	
	// извлечение из строки еще одной цифры
	for(int i = 0; i < 10 ; i++)
	{
		if(massive[i] == *ch1)
		{
			numberOne = i;
			controlCh1 = true;
		}
		if(massive[i] == *ch2)
		{
			numberTwo = i;
			controlCh2 = true;
		}
		// прекращаем поиск, если элементы уже найдены
		if(controlCh1 && controlCh2)
		{
			return stringNumber(ch1, numberOne) > stringNumber(ch2, numberTwo) ? true : false; 
		}
		// если до этого была одна цифра
		else if(i == 9 && flag)
		{
			ch1++;
			ch2++;
			return compareChars(ch1, ch2, counterNumber) ? true : false;  
		}
		// если до этого были обе цифры - требуется для редкого исключения
		else if(i == 9 && !flag)
		{
			ch1++;
			ch2++;
			// запускаем реальный рекурсивный цикл
			return stringNumber(ch1, 0) > stringNumber(ch2, 0) ? true : false; 
		}
	}
}
// get numeral
int stringNumber(const char *ch, int sum)
{
	int number = NULL;
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

	// увеличиваем
	sum = sum*10 + number;
	// следующий символ
	*ch++;
	// если кончилась строка
	if(*ch == NULL)
	{
		return sum;
	}
	// рекурсия
	stringNumber(ch, sum);
}
// compare two symbols
bool compareChars(const char *ch1, const char *ch2, int counterNumber)
{
	// распологать символы в таком порядке
	const char *order = ".01234567890'- !#$%&(),[]^_`{}~+ABCDEFGHIJKLMNOPQRSTUVWXYZ№АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	// почему будем сравнивать
	int orderNumberOne = 0;
	int orderNumberTwo = 0;
	// контроллеры поиска
	bool controlOrderNumberOne = false;
	bool controlOrderNumberTwo = false;

	// нахождение символов
	for(int i = 0; i < strlen(order) ; i++)
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
