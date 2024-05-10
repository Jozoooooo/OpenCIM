#pragma once

#include <QMainWindow>
#include "ModelWidget.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    void initUi();

public:
    MainWindow();

    static void initEntityFile(const QString &filePath, bool init = true);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};