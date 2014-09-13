#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QDialogButtonBox;
class QGroupBox;
class QGridLayout;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QStringList;
class QTextEdit;
class QWidget;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
        void about();
        void browse();
        void rename();
        void more();

private:
        bool toogle;
        void createActions();
        void createMenus();
        void myCoolRename(int);
        QString convertToMyCompleteSuffix(QString);

        // путь к директории для переименования
        QString directoryName;
        // последняя директория
        QString lastDirectory;

        // case - descending sort or ascending sort
        QCheckBox *descendingSort;
        // меня для установки и выхода
        QMenu *fileMenu;
        // меня для помощи
        QMenu *helpMenu;
        // для установления директории
        QAction *openAct;
        // для закрытия
        QAction *exitAct;
        // для справки о программе
        QAction *aboutAct;
        // для справки о QT4
        QAction *aboutQtAct;

        // кнопки
        QPushButton *renameButton;
        QPushButton *quitButton;
        QPushButton *browseButton;
        QPushButton *moreButton;
        // объединение двух кнопок
        QDialogButtonBox *buttonBox;
        QGroupBox *hideBox;
        // выбор
        QComboBox *sortComboBox;
        QComboBox *directoryComboBox;
        QComboBox *renameComboBox;
        // первое число добавленное к файлу
        QSpinBox *numberStarter;
        // вывод нужной инфы
        QTextEdit *nameBeforeRename;
        QTextEdit *nameAfterRename;

        // метки
        QLabel *pathLabel;
        QLabel *renameLabel;
        QLabel *sortLabel;
        QLabel *numberLabel;
        QLabel *descendingLabel;
        QLabel *beforeLabel;
        QLabel *afterLabel;
        QLabel *lastNumberLabel;
        // текстовая строка
        QLineEdit *lastNumberAfterRename;

        QWidget *widget;
        QGridLayout *mainLayout;

        /********************************************************************
                Моя сортировка
        ********************************************************************/
        QStringList sortStringList(QStringList);

        friend void bubbleSort(QStringList &,           bool up_d = 0);
        friend void quickSort (QStringList &, int, int, bool up_d = 0);
        friend bool operator< (std::string, std::string);
        friend bool operator> (std::string, std::string);
        friend bool compareChars(const char *, const char *, int);
        friend int  getNumber(const char *, int);
};

#endif
