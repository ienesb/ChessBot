#ifndef BLOCK
#define BLOCK

class Block : public QLabel{
    private:
    Piece* piece;
    Game* game;
    std::string color; // "w" or "b"
    int x; //coordinates
    int y;

    public:
    void mousePressEvent(QMouseEvent *ev);
    Block(QDialog *Dialog, Game* game, int x, int y, Piece* piece=nullptr);
    void setPiece(Piece* piece);
    Piece* getPiece();
    vector<int> getCoordinates();
    std::string getColor();

};

#endif