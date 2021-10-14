import cv2
import numpy as np

import os

PNGS = "pngs/pieces"

class Pozition():
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

    def as_str(self):
        return f"{int(self.row)}-{int(self.column)}"

class Piece():
    def __init__(self, color, pozition:Pozition):
        self.color = color
        self.pozition = pozition

    
    def move(self, board, target:Pozition):
        if self.pozition == target:
            return -6
        if target.column > 8 or target.column < 1 or target.row > 8 or target.row > 1:
            return -5
        if self.color == board[target].color:
            return -3
        return 0


class At(Piece):
    def __init__(self, color, pozition: Pozition):
        self.pngname = os.path.join(PNGS, "at.png")
        super().__init__(color, pozition)

    def move(self, board, target:Pozition):  
        if super().move(board, target):
            super().move(board, target)
                
        statements1 = []
        statements1.append(((self.pozition.column + 1 == target.pozition.column) and (self.pozition.row + 2 == target.pozition.row)))
        statements1.append(((self.pozition.column + 2 == target.pozition.column) and (self.pozition.row + 1 == target.pozition.row)))
        statements1.append(((self.pozition.column + 1 == target.pozition.column) and (self.pozition.row - 2 == target.pozition.row)))
        statements1.append(((self.pozition.column + 2 == target.pozition.column) and (self.pozition.row - 1 == target.pozition.row)))
        statements1.append(((self.pozition.column - 1 == target.pozition.column) and (self.pozition.row + 2 == target.pozition.row)))
        statements1.append(((self.pozition.column - 2 == target.pozition.column) and (self.pozition.row + 1 == target.pozition.row)))
        statements1.append(((self.pozition.column - 1 == target.pozition.column) and (self.pozition.row - 2 == target.pozition.row)))
        statements1.append(((self.pozition.column - 2 == target.pozition.column) and (self.pozition.row - 1 == target.pozition.row)))
        
        if not(True in statements1):
            return -1

        return 0


class Fil(Piece):
    def __init__(self, color, pozition: Pozition):
        self.pngname = os.path.join(PNGS, "fil.png")
        super().__init__(color, pozition)

    def move(self, board, target:Pozition):
        if super().move(board, target):
            super().move(board, target)

        coldif = abs(self.pozition.column - target.column)
        rowdif = abs(self.pozition.row - target.row)
        
        if not coldif == rowdif:
            return -1

        colstep = 1 if self.pozition.column < target.column else -1
        rowstep = 1 if self.pozition.row < target.row else -1
        
        for i in range(1,coldif):
            tempPos = Pozition(row=self.pozition.row+rowstep*i, column=self.pozition.column+colstep*i)
            if board[tempPos]:
                return -2

        return 0


class Kale(Piece):
    def __init__(self, color, pozition: Pozition):
        self.pngname = os.path.join(PNGS, "kale.png")
        super().__init__(color, pozition)

    def move(self, board, target:Pozition):
        if super().move(board, target):
            super().move(board, target)

        coldif = abs(self.pozition.column - target.column)
        rowdif = abs(self.pozition.row - target.row)
        
        if coldif > 0 and rowdif > 0:
            return -1
        
        if self.pozition.column < target.column:
            colstep = 1
        elif self.pozition.column > target.column:
            colstep = -1
        else:
            colstep = 0

        if self.pozition.row < target.row:
            rowstep = 1
        elif self.pozition.row > target.row:
            rowstep = -1
        else:
            rowstep = 0

        for i in range(1,coldif+rowdif):
            tempPos = Pozition(row=self.pozition.row+rowstep*i, column=self.pozition.column+colstep*i)
            if board[tempPos]:
                return -2


        return 0


class Vezir(Piece):
    def __init__(self, color, pozition: Pozition):
        self.pngname = os.path.join(PNGS, "vezir.png")
        super().__init__(color, pozition)

    def move(self, board, target:Pozition):
        if super().move(board, target):
            super().move(board, target)

        coldif = abs(self.pozition.column - target.column)
        rowdif = abs(self.pozition.row - target.row)

        if not(coldif == 0 or rowdif == 0 or coldif == rowdif):
            return -1
        
        if coldif == 0 or rowdif == 0:

            if self.pozition.column < target.column:
                colstep = 1
            elif self.pozition.column > target.column:
                colstep = -1
            else:
                colstep = 0

            if self.pozition.row < target.row:
                rowstep = 1
            elif self.pozition.row > target.row:
                rowstep = -1
            else:
                rowstep = 0

            for i in range(1,coldif+rowdif):
                tempPos = Pozition(row=self.pozition.row+rowstep*i, column=self.pozition.column+colstep*i)
                if board[tempPos]:
                    return -2

        else:
            colstep = 1 if self.pozition.column < target.column else -1
            rowstep = 1 if self.pozition.row < target.row else -1
            
            for i in range(1,coldif):
                tempPos = Pozition(row=self.pozition.row+rowstep*i, column=self.pozition.column+colstep*i)
                if board[tempPos]:
                    return -2



        return 0


class Sah(Piece):
    def __init__(self, color, pozition: Pozition):
        self.pngname = os.path.join(PNGS, "sah.png")
        super().__init__(color, pozition)

    def move(self, board, target:Pozition):
        if super().move(board, target):
            super().move(board, target)

        coldif = abs(self.pozition.column - target.column)
        rowdif = abs(self.pozition.row - target.row)

        if coldif <= 1 and rowdif <=1:
            return -1

        return 0
        

class Piyon(Piece):
    def __init__(self, color, pozition: Pozition):
        self.pngname = os.path.join(PNGS, "piyon.png")
        super().__init__(color, pozition)

    def move(self, board, target:Pozition):
        if super().move(board, target):
            super().move(board, target)

        if self.color == "w":
            if not (self.pozition.row + 1 == target.row and self.pozition.column == target.column):
                return -1

            return 0

        else:
            if not (self.pozition.row - 1 == target.row and self.pozition.column == target.column):
                return -1

            return 0

    
        
if __name__ == "__main__":
    pass