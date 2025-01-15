#ifndef NEWCHANNELDIALOG_H
#define NEWCHANNELDIALOG_H

#include <QDialog>
#include <QStringList>
#include <windows.h>


namespace Ui {
class NewChannelDialog;
}

class NewChannelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewChannelDialog(QWidget *parent = nullptr);
    ~NewChannelDialog();

private slots:
    //void on_buttonBox_accepted();

private:
    Ui::NewChannelDialog *ui;

    QStringList getAvailableChannels();
};

#endif // NEWCHANNELDIALOG_H
