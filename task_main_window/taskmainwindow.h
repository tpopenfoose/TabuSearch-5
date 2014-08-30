#ifndef TASKMAINWINDOW_H
#define TASKMAINWINDOW_H

#include "toolbar.h"
#include "statusbox.h"
#include "progressbox.h"
#include "scrollarea.h"
#include <QMainWindow>
#include <QMessageBox>

class TaskMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TaskMainWindow();
    void display_result(const Result & p_result, const ConfigData& p_data, int p_option);
signals:
    void random_button_clicked();
    void start_button_clicked();
    void config_button_clicked();
    void pause_button_clicked(bool);
    void clear_message_box_button(QMessageBox::StandardButton p_button);
    void thread_finished();
    void delete_task();
    void exit_button_clicked();
public slots:
    void update_progress(int value,int all,int time);
    void thread_finished(int p_action);
    void process_exit(bool p_only_button);
private slots:
    void save_action();
    void load_action();

    void random_action();
    void start_action();
    void config_action();
    void pause_action(bool p_flag);

    void data_base_action();
    void clear_action();

    void maximize_action(bool p_toggle);
    void exit_action();

private:

    std::unique_ptr<ToolBar> m_toolbar;
    std::unique_ptr<StatusBox> m_status_box;
    std::unique_ptr<ProgressBox> m_progress_box;
    std::unique_ptr<ScrollArea> m_scroll_area;
    std::unique_ptr<QMessageBox> m_msgBox;

    bool m_calculations_in_progress;
    bool m_save;

    void create_tool_bar(void);
    void create_connections(void);
    void create_status_box(void);
    void create_progres_box(void);
    void create_scroll_area(void);
    void create_dock_boxes(void);
    void try_delete_task();
    void try_to_save();
    void inform_about_calculations();
};

#endif // TASKMAINWINDOW_H
