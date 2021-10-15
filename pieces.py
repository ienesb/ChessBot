import cv2
import numpy as np

import os

PNGS = "pngs/pieces"

class Position():
    def __init__(self, row, column):
        self.row = row
        self.column = column
        if (column + row)%2 == 0:
            self.color = "w"
        else:
            self.color = "b"
    
    def __eq__(self, o) -> bool:
        if o.row == self.row and o.column == self.column:
            return True
        return False

    def asStr(self):
        return f"{int(self.row)}-{int(self.column)}"

class Piece():
    def __init__(self, color, position:Position):
        self.color = color
        self.position = position
        self.is_active = True

    def performMovement(self, target:Position):
        self.position = target

    def move(self, board, target:Position):
        if self.position == target:
            return -6
        if target.column > 8 or target.column < 1 or target.row > 8 or target.row > 1:
            return -5
        if hasattr(board[target.asStr()], "color") and self.color == board[target.asStr()].color:
            return -3
        return 0

    def kill(self) -> None:
        self.is_active = False

class At(Piece):
    def __init__(self, color, position: Position):
        self.pngname = os.path.join(PNGS, "at.png")
        super().__init__(color, position)

    def move(self, board, target:Position):  
        if super().move(board, target):
            super().move(board, target)
                
        statements1 = []
        statements1.append(((self.position.column + 1 == target.column) and (self.position.row + 2 == target.row)))
        statements1.append(((self.position.column + 2 == target.column) and (self.position.row + 1 == target.row)))
        statements1.append(((self.position.column + 1 == target.column) and (self.position.row - 2 == target.row)))
        statements1.append(((self.position.column + 2 == target.column) and (self.position.row - 1 == target.row)))
        statements1.append(((self.position.column - 1 == target.column) and (self.position.row + 2 == target.row)))
        statements1.append(((self.position.column - 2 == target.column) and (self.position.row + 1 == target.row)))
        statements1.append(((self.position.column - 1 == target.column) and (self.position.row - 2 == target.row)))
        statements1.append(((self.position.column - 2 == target.column) and (self.position.row - 1 == target.row)))
        
        if not(True in statements1):
            return -1

        return 0


class Fil(Piece):
    def __init__(self, color, position: Position):
        self.pngname = os.path.join(PNGS, "fil.png")
        super().__init__(color, position)

    def move(self, board, target:Position):
        if super().move(board, target):
            super().move(board, target)

        coldif = int(abs(self.position.column - target.column))
        rowdif = int(abs(self.position.row - target.row))
        
        if not coldif == rowdif:
            return -1

        colstep = 1 if self.position.column < target.column else -1
        rowstep = 1 if self.position.row < target.row else -1
        
        for i in range(1,coldif):
            tempPos = Position(row=self.position.row+rowstep*i, column=self.position.column+colstep*i)
            if board[tempPos.asStr()]:
                return -2

        return 0


class Kale(Piece):
    def __init__(self, color, position: Position):
        self.pngname = os.path.join(PNGS, "kale.png")
        super().__init__(color, position)

    def move(self, board, target:Position):
        if super().move(board, target):
            super().move(board, target)

        coldif = int(abs(self.position.column - target.column))
        rowdif = int(abs(self.position.row - target.row))
        
        if coldif > 0 and rowdif > 0:
            return -1
        
        if self.position.column < target.column:
            colstep = 1
        elif self.position.column > target.column:
            colstep = -1
        else:
            colstep = 0

        if self.position.row < target.row:
            rowstep = 1
        elif self.position.row > target.row:
            rowstep = -1
        else:
            rowstep = 0

        for i in range(1,coldif+rowdif):
            tempPos = Position(row=self.position.row+rowstep*i, column=self.position.column+colstep*i)
            if board[tempPos.asStr()]:
                return -2

        return 0


class Vezir(Piece):
    def __init__(self, color, position: Position):
        self.pngname = os.path.join(PNGS, "vezir.png")
        super().__init__(color, position)

    def move(self, board, target:Position):
        if super().move(board, target):
            super().move(board, target)

        coldif = int(abs(self.position.column - target.column))
        rowdif = int(abs(self.position.row - target.row))

        if not(coldif == 0 or rowdif == 0 or coldif == rowdif):
            return -1
        
        if coldif == 0 or rowdif == 0:

            if self.position.column < target.column:
                colstep = 1
            elif self.position.column > target.column:
                colstep = -1
            else:
                colstep = 0

            if self.position.row < target.row:
                rowstep = 1
            elif self.position.row > target.row:
                rowstep = -1
            else:
                rowstep = 0

            for i in range(1,coldif+rowdif):
                tempPos = Position(row=self.position.row+rowstep*i, column=self.position.column+colstep*i)
                if board[tempPos.asStr()]:
                    return -2

        else:
            colstep = 1 if self.position.column < target.column else -1
            rowstep = 1 if self.position.row < target.row else -1
            
            for i in range(1,coldif):
                tempPos = Position(row=self.position.row+rowstep*i, column=self.position.column+colstep*i)
                if board[tempPos.asStr()]:
                    return -2

        return 0


class Sah(Piece):
    def __init__(self, color, position: Position):
        self.pngname = os.path.join(PNGS, "sah.png")
        super().__init__(color, position)

    def move(self, board, target:Position):
        if super().move(board, target):
            super().move(board, target)

        coldif = int(abs(self.position.column - target.column))
        rowdif = int(abs(self.position.row - target.row))

        if coldif > 1 or rowdif > 1:
            return -1

        return 0
        

class Piyon(Piece):
    def __init__(self, color, position: Position):
        self.pngname = os.path.join(PNGS, "piyon.png")
        super().__init__(color, position)

    def move(self, board, target:Position):
        if super().move(board, target):
            super().move(board, target)

        if self.color == "w":
            if not (self.position.row + 1 == target.row and self.position.column == target.column):
                return -1
            return 0

        else:
            if not (self.position.row - 1 == target.row and self.position.column == target.column):
                return -1
            return 0
        
if __name__ == "__main__":
    pass