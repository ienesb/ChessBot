def parseNotation(n):
    
    n = n.replace("+", "") # sah ceker
    n = n.replace("x", "") # tas yer
    n = n.replace("#", "") # mat eder

    if "=" in n:
        n = n[:n.index("=")]

    if n[0] == "O":
        return "K", 0, 0, 0
        
    elif n[0] in "NBRQK":
        pieceName = n[0]
    else:
        pieceName = "P"

    d = {"a":1, "b":2, "c":3, "d":4, "e":5, "f":6, "g":7, "h":8}

    y = int(n[-1])
    x = d[n[-2]]

    l = len(n)-2

    if not pieceName == "P":
        l -= 1

    coord = 0

    if l == 1:
        coord = n[-3]
        try:
            coord = int(coord)
        except ValueError:
            pass
    
    return pieceName, x, y, coord


j = 0
with open("ficsgamesdb_202101_chess_nomovetimes_240114.pgn", "r") as f:
    for line in f.readlines():
        try:
            if line[0].isdigit():
                j+=1
                with open(f"games/game{j}.txt", "w") as fw:
                    if "0-1" in line:
                        winner = {"w":"1", "b":"-1"}
                    elif "1-0" in line:
                        winner = {"w":"-1", "b":"1"}
                    else:
                        winner = {"w":"0", "b":"0"}

                    moves = line.split(". ")
                    for i in range(1, len(moves)):
                        wMove, bMove = moves[i].split(" ")[:2]
                        wPiece, wTargetX, wTargetY, wPos = parseNotation(wMove)
                        fw.write(f"{wPiece} {wTargetX} {wTargetY} {wPos} " + winner["w"] + "\n") 
                        if not "{" in bMove:
                            bPiece, bTargetX, bTargetY, bPos = parseNotation(bMove)
                            fw.write(f"{bPiece} {bTargetX} {bTargetY} {bPos} " + winner["b"] + "\n") 
                    
        except IndexError:
            continue
