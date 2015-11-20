#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
    class MainWindow;
}

// This class is a singleton

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        ~MainWindow();
        static MainWindow* get();
        void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
        void newGame();

    private:
        Q_DISABLE_COPY(MainWindow)
        MainWindow();
        void currentPageChanged(int index);
        static MainWindow* instance;
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
