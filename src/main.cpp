#include <QApplication>
#include <QLabel>

#include <board.hpp>
#include <game.hpp>
#include <types.hpp>

int main1(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QLabel label("Hello, World from Qt6!");
    label.show();
    return app.exec();
}

int main2(int argc, char *argv[]) {
    auto b = Board::instance();
    b.resize(3, 3);
    b[0][0] = 0x02;
    b[0][1] = 0x01;
    b[0][2] = 0x01;
    b[1][0] = 0x14;
    b[1][1] = 0x21;
    b[1][2] = 0x01;
    b[2][0] = 0x02;
    b[2][1] = 0x02;
    b[2][2] = 0x18;
    b.print();
    return 0;
}

int main(int argc, char *argv[]) {
    // Initialize and run the game
    Game &game = Game::instance();
    if (game.initialize()) {
        game.run();
    }
    return 0;
}
