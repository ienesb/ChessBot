from PyQt5 import QtCore, QtGui, QtWidgets
from pieces import *

class Block(QtWidgets.QLabel):
    labels = {}
    BLOCK_COLORS = {"w": [180,180,180], "b": [86,120,100], "r": [0,0,255]}
    PIECE_COLORS = {"w":255, "b":54}

    def __init__(self, widget:QtWidgets.QWidget, name:tuple):
        super().__init__(widget)
        self.is_selected = False
        self.name = name
        self.Y, self.X = name
        self.X = 7 - self.X
        self.pozition = Pozition(self.X+1, self.Y+1)
        self.pngname = os.path.join(".temp", f"{self.name}.png")
        Block.labels[name] = self

        if (self.X + self.Y) % 2 == 0:
            self.color = "b"
        else:
            self.color = "w"
        self.piece = None
    
    def setPiece(self, piece):
        self.piece = piece


    def mousePressEvent(self, ev: QtGui.QMouseEvent) -> None:
        if self.is_selected:
            self.is_selected = False
        else:
            Block.setFalse()
            self.is_selected = True
        Block.update()


    @staticmethod
    def setFalse():
        for i in Block.labels:
            Block.labels[i].is_selected = False
            Block.labels[i].setPixmap(QtGui.QPixmap(Block.labels[i].pngname))
    

    @staticmethod
    def update():
        for i in Block.labels:
            img = np.zeros((200,200,3), dtype=np.uint8)
            color = Block.BLOCK_COLORS[Block.labels[i].color]
            if Block.labels[i].is_selected:
                color = Block.BLOCK_COLORS["r"]

            img[:,:,:] = color
            if Block.labels[i].piece:
                piecePng = cv2.imread(Block.labels[i].piece.pngname, 0)
                img[piecePng==255] = Block.PIECE_COLORS[Block.labels[i].piece.color]
            cv2.imwrite(Block.labels[i].pngname, img)
            Block.labels[i].setPixmap(QtGui.QPixmap(Block.labels[i].pngname))
        


class Game(object):
    def __init__(self, centralwidget):
        self.turn = "w"
        self.board = {}
        
        for i in range(1,9):
            for j in range(1,9):
                pos = Pozition(i,j)
                self.board[pos.as_str()] = None

        self.setPiece(Piyon("b", Pozition(7, 1)))
        self.setPiece(Piyon("b", Pozition(7, 2)))
        self.setPiece(Piyon("b", Pozition(7, 3)))
        self.setPiece(Piyon("b", Pozition(7, 4)))
        self.setPiece(Piyon("b", Pozition(7, 5)))
        self.setPiece(Piyon("b", Pozition(7, 6)))
        self.setPiece(Piyon("b", Pozition(7, 7)))
        self.setPiece(Piyon("b", Pozition(7, 8)))
        self.setPiece(At("b", Pozition(8, 2)))
        self.setPiece(Fil("b", Pozition(8, 3)))
        self.setPiece(Kale("b", Pozition(8, 1)))
        self.setPiece(At("b", Pozition(8, 7)))
        self.setPiece(Fil("b", Pozition(8, 6)))
        self.setPiece(Kale("b", Pozition(8, 8)))
        self.setPiece(Vezir("b", Pozition(8, 4)))
        self.setPiece(Sah("b", Pozition(8, 5)))

        self.setPiece(Piyon("w", Pozition(2, 1)))
        self.setPiece(Piyon("w", Pozition(2, 2)))
        self.setPiece(Piyon("w", Pozition(2, 3)))
        self.setPiece(Piyon("w", Pozition(2, 4)))
        self.setPiece(Piyon("w", Pozition(2, 5)))
        self.setPiece(Piyon("w", Pozition(2, 6)))
        self.setPiece(Piyon("w", Pozition(2, 7)))
        self.setPiece(Piyon("w", Pozition(2, 8)))
        self.setPiece(At("w", Pozition(1, 2)))
        self.setPiece(Fil("w", Pozition(1, 3)))
        self.setPiece(Kale("w", Pozition(1, 1)))
        self.setPiece(At("w", Pozition(1, 7)))
        self.setPiece(Fil("w", Pozition(1, 6)))
        self.setPiece(Kale("w", Pozition(1, 8)))
        self.setPiece(Vezir("w", Pozition(1, 4)))
        self.setPiece(Sah("w", Pozition(1, 5)))

        self.blocks = []
        for i in range(64):
            SIZE = 100
            x = (i%8)*SIZE
            y = (i//8)*SIZE
            block = Block(centralwidget, name=(x/SIZE,y/SIZE))
            block.setGeometry(QtCore.QRect(x, y, SIZE, SIZE))
            block.setScaledContents(True)
            block.setPiece(self.getPieceAt(block.pozition))
        
        Block.update()

    def getPieceAt(self, pozition:Pozition):
        return self.board[pozition.as_str()]

    def setPiece(self, piece:Piece):
        self.board[piece.pozition.as_str()] = piece

    def changePiece(self, piece:Piece, pozition:Pozition):
        self.board[piece.pozition.as_str()] = None
        self.board[pozition.as_str()] = piece

    def getPieces(self):
        pass
        # get list of pieces from board with double for loop
    
   
    def checkMovement(self, piece, target):
        self.pieces[piece].move(self.board, target)



class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1600, 1600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")

        self.game = Game(self.centralwidget)

        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)


    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
