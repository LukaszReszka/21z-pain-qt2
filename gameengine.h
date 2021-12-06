#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include<QObject>
#include <QString>

class GameEngine: public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString boardToShow READ getBoard NOTIFY boardToShowChanged)
    Q_PROPERTY(QString message READ getMessage NOTIFY messageChanged)

    GameEngine(QObject* parent = nullptr);
    QString getBoard() {
        return boardToShow;
    }

    QString getMessage() {
        return message;
    }

private:
    int whitesMovesToCheckBoard[8][8];
    int blacksMovesToCheckBoard[8][8];
    std::string avaiableMoves[8][8];
    QString message = QString();
    QString boardToShow = QString(64, NONE);
    bool isBlacksTurn;
    bool areMovesToMake;
    bool hasGameEnded;
    enum {BLACK = 'B', WHITE = 'W', NONE = '-', BLACK_PAWN = -2, WHITE_PAWN = -1, NOT_TO_CHECK = 0,
          N = '0', S = '1', E = '2', W = '3', NE = '4', NW = '5', SE = '6', SW = '7'
    };

    void markNeighbours(int row, int col, bool isWorthChecking,
                                  int tab[8][8]);
    void clearAvaiableMovesTab();
    void markAllAvaiablePositions();
    void checkPosition(int row, int col);
    void swapPawnsInLine(int start_x, int start_y, char direction);
    void swapPawns(int field_x, int field_y);

    public slots:
    void processPlayersMove(int x, int y);
    void resetGame();

signals:
    void boardToShowChanged();
    void messageChanged();
};

#endif // GAMEENGINE_H
