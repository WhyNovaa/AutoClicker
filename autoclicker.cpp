#include "autoclicker.h"
#include "ui_autoclicker.h"

AutoClicker::AutoClicker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AutoClicker)
{
    ui->setupUi(this);

    this->setFixedSize(400, 180);
    this->setWindowFlag(Qt::WindowStaysOnTopHint, true);

    ui->click_per_sec_spinBox->setMaximum(1000);

    //qDebug() << GetSystemMetrics(SM_CXSCREEN) << Qt::endl;
    //qDebug() << GetSystemMetrics(SM_CYSCREEN) << Qt::endl;

    ui->x_lineEdit->setValidator(new QIntValidator(0, GetSystemMetrics(SM_CXSCREEN)));
    ui->y_lineEdit->setValidator(new QIntValidator(0, GetSystemMetrics(SM_CYSCREEN)));


    QFont info_font;
    info_font.setBold(true);
    info_font.setPixelSize(15);

    ui->start_button_label->setFont(info_font);
    ui->finish_button_label->setFont(info_font);

    this->setStyleSheet("QMainWindow{background: #D3D3D3;}");

    ui->pick_pos_pButton->setStyleSheet("QPushButton{background: #87CEFA;"
                                        " color: #313240; font-size: 14px;}"
                                        "QPushButton:hover{background: #87CEFA; border:2px; border-style:solid; border-color: #000080;}");
    ui->pick_cur_pos_rButton->setStyleSheet("QRadioButton{color: #313240; font-size: 14px;}");

}

AutoClicker::~AutoClicker()
{
    delete ui;
}

void AutoClicker::setButtonsEnabled(const bool& flag) {
    ui->x_lineEdit->setEnabled(flag);
    ui->y_lineEdit->setEnabled(flag);
    ui->pick_pos_pButton->setEnabled(flag);
}

void AutoClicker::on_pick_cur_pos_rButton_toggled(bool checked)
{
    if(checked) {
        ui->pick_writed_pos_rButton->setChecked(false);

        setButtonsEnabled(false);
    }
    else if(!ui->pick_writed_pos_rButton->isChecked()) {
        ui->pick_cur_pos_rButton->setChecked(true);
    }
}


void AutoClicker::on_pick_writed_pos_rButton_toggled(bool checked)
{
    if(checked) {
        ui->pick_cur_pos_rButton->setChecked(false);

        setButtonsEnabled(true);
    }
    else if(!ui->pick_cur_pos_rButton->isChecked()) {
        ui->pick_writed_pos_rButton->setChecked(true);
    }
}


void AutoClicker::on_pick_pos_pButton_clicked()
{
    ui->pick_pos_pButton->setDisabled(true);
    int x = ui->x_lineEdit->text().toInt();
    int y = ui->y_lineEdit->text().toInt();
    int delay = ui->click_per_sec_spinBox->text().toInt();

    setButtonsEnabled(false);

    while(true) {
        qDebug() << "Clicking..." << Qt::endl;

        SetCursorPos(x, y);
        mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

        Sleep(delay);
        if (GetAsyncKeyState(VK_F2))
        {
            qDebug() << "Ending..." << Qt::endl;
            setButtonsEnabled(true);
            break;
        }
    }
}

void AutoClicker::keyPressEvent(QKeyEvent * e) {
    if(e->key() == Qt::Key_F1 && ui->pick_cur_pos_rButton->isEnabled()) {

        POINT cursor_point;
        GetCursorPos(&cursor_point);
        int x = cursor_point.x;
        int y = cursor_point.y;

        int delay = ui->click_per_sec_spinBox->text().toInt();
        ui->x_lineEdit->setText(QString::number(x));
        ui->y_lineEdit->setText(QString::number(y));

        while(true) {
            qDebug() << "Clicking..." << Qt::endl;

            SetCursorPos(x, y);
            mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

            Sleep(delay);
            if (GetAsyncKeyState(VK_F2))
            {
                qDebug() << "Ending..." << Qt::endl;
                setButtonsEnabled(true);
                break;
            }
        }
    }
}
