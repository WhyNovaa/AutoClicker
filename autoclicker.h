#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H

#include <QMainWindow>
#include <QApplication>
#include <qDebug>
#include <QKeyEvent>
#include <Windows.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class AutoClicker;
}
QT_END_NAMESPACE

class AutoClicker : public QMainWindow
{
    Q_OBJECT

public:
    AutoClicker(QWidget *parent = nullptr);
    ~AutoClicker();

    void setButtonsEnabled(const bool& flag);

    virtual void keyPressEvent(QKeyEvent * e);
private slots:
    void on_pick_cur_pos_rButton_toggled(bool checked);

    void on_pick_writed_pos_rButton_toggled(bool checked);

    void on_pick_pos_pButton_clicked();

private:
    Ui::AutoClicker *ui;
};
#endif // AUTOCLICKER_H
