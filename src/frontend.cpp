#include <QApplication>
#include <QMainWindow>
#include <QPushButton>

int main2(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    QPushButton button("Click me", &window);

    window.setGeometry(100, 100, 300, 200);
    button.setGeometry(50, 50, 100, 30);
    QObject::connect(&button, &QPushButton::clicked, []() {
        qDebug() << "Button clicked!";
    });

    window.show();
    return app.exec();
}
