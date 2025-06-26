#include <QApplication>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QApplication>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QFontDatabase>
#include "pythagoras_tree.h"
#include "pythagoras_tree.c"

class AsciiArtWidget : public QWidget {
public:
    AsciiArtWidget(QWidget* parent = nullptr) : QWidget(parent) {
        QHBoxLayout* layout = new QHBoxLayout(this);
        textEdit = new QPlainTextEdit(this);
        textEdit->setReadOnly(true);
        QFont font("Courier", 10);
        textEdit->setFont(font);

        layout->addWidget(textEdit);

        const int width = 80;
        const int height = 40;
        char buffer[(width + 1) * height];

        generate_pythagoras_tree(buffer, width, height, 10);

        textEdit->setPlainText(QString::fromLatin1(buffer));
    }

private:
    QPlainTextEdit* textEdit;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AsciiArtWidget widget;
    widget.resize(800, 600);
    widget.setWindowTitle("Дерево Пифагора");
    widget.show();

    return app.exec();
}
