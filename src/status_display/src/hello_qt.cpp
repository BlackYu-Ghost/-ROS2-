#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char *argv[]){
    
    QApplication app(argc, argv);
    QLabel* label = new QLabel();
    QString message = QString::fromStdString("Hello, Qt!");
    label->setText(message);
    label->setAlignment(Qt::AlignCenter);
    label->resize(400, 200);
    label->show();
    return app.exec();

}