#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QToolBar>
#include <QAction>
#include <QObject>


class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    ToolBar();

signals:
    void save_button_clicked();
    void load_button_clicked();

    void random_button_clicked();
    void start_button_clicked();
    void config_button_clicked();
    void pause_button_clicked(bool p_toggle);

    void dataBase_button_clicked();
    void clear_button_clicked();

    void minimize_button_clicked();
    void maximize_button_clicked(bool p_toggle);
    void exit_button_clicked();
public slots:
    void clear_message_box_button(int p_button);
    void thread_finished();

private slots:
    void save_action();
    void load_action();

    void random_action();
    void start_action();
    void config_action();
    void pause_action(bool p_toggle);

    void dataBase_action();
    void clear_action();

    void minimize_action();
    void maximize_action(bool p_toggle);
    void exit_action();

private:
    QAction *saveAction;
    QAction *loadAction;

    QAction *configAction;
    QAction *randomAction;
    QAction *startAction;
    QAction *pauseAction;

    QAction *databaseAction;
    QAction *clearAction;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *exitAction;
    void createActions(void);
    void createConnections(void);
};

#endif // TOOLBAR_H
