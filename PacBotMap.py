from turtle import *

class LOI:
        def __init__(self, data):   #[x, y, can_up, can_right, can_down, can_left]
            self.coords = (data[0], data[1])
            self.canMove = (data[2], data[3], data[4], data[5])
            
        def getCoords(self):
            return self.coords
        
        def getX(self):
            return self.coords[0]
        
        def getY(self):
            return self.coords[1]
        
        def canMoveUp(self):
            return self.canMove[0]
        
        def canMoveRight(self):
            return self.canMove[1]
        
        def canMoveDown(self):
            return self.canMove[2]
        
        def canMoveLeft(self):
            return self.canMove[3]

class PacBotArena:
    def drawMap(self):
        shape("circle")
        
        for row in self.map:
            for location in row:
                penup()
                if location != None:
                    goto(location.getX()*5, location.getY()*5)
                    stamp()

    def __init__(self):#ORIGIN IS AT STARTING LOCATION
        L00 = [-43.75, 77, False, True, True, False]
        L01 = [-26.25, 77, False, True, True, True]
        L02 = [-5.25, 77, False, False, True, True]
        L03 = [5.25, 77, False, True, True, False]
        L04 = [26.25, 77, False, True, True, True]
        L05 = [43.75, 77, False, False, True, True]


        L10 = [-43.75, 63, True, True, True, False]
        L11 = [-26.25, 63, True, True, True, True]
        L12 = [-15.75, 63, False, True, True, True]
        L13 = [-5.25, 63, True, True, False, True]
        L14 = [5.25, 63, True, True, False, True]
        L15 = [15.75, 63, False, True, True, True]
        L16 = [26.25, 63, True, True, True, True]
        L17 = [43.75, 63, True, False, True, True]


        L20 = [-43.75, 52.5, True, True, False, False]
        L21 = [-26.25, 52.5, True, False, True, True]
        L22 = [-15.75, 52.5, True, True, False, False]
        L23 = [-5.25, 52.5, False, False, True, True]
        L24 = [5.25, 52.5, False, True, True, False]
        L25 = [15.75, 52.5, True, False, False, True]
        L26 = [26.25, 52.5, True, True, True, False]
        L27 = [43.75, 52.5, True, False, False, True]


        L30 = [-15.75, 42, False, True, True, False]
        L31 = [-5.25, 42, True, True, False, True]
        L32 = [5.25, 42, True, True, False, True]
        L33 = [15.75, 42, False, False, True, True]


        L40 = [-26.25, 31.5, True, True, True, False]
        L41 = [-15.75, 31.5, True, False, True, True]
        L42 = [15.75, 31.5, True, True, True, False]
        L43 = [26.25, 31.5, True, False, True, True]


        L50 = [-15.75, 21, True, True, True, False]
        L51 = [15.75, 21, True, False, True, True]


        L60 = [-43.75, 10.5, False, True, True, False]
        L61 = [-26.25, 10.5, True, True, True, True]
        L62 = [-15.75, 10.5, True, True, False, True]
        L63 = [-5.25, 10.5, False, False, True, True]
        L64 = [5.25, 10.5, False, True, True, False]
        L65 = [15.75, 10.5, True, True, False, True]
        L66 = [26.25, 10.5, True, True, True, True]
        L67 = [43.75, 10.5, False, False, True, True]


        L70 = [-43.75, 0, True, True, False, False]
        L71 = [-36.75, 0, False, False, True, True]
        L72 = [-26.25, 0, True, True, True, False]
        L73 = [-15.75, 0, False, True, True, True]
        L74 = [-5.25, 0, True, True, False, True]
        L75 = [5.25, 0, True, True, False, True]
        L76 = [15.75, 0, False, True, True, True]
        L77 = [26.25, 0, True, False, True, True]
        L78 = [36.75, 0, False, True, True, False]
        L79 = [43.75, 0, True, False, False, True]


        L80 = [-43.75, -10.5, False, True, True, False]
        L81 = [-36.75, -10.5, True, True, False, True]
        L82 = [-26.25, -10.5, True, False, False, True]
        L83 = [-15.75, -10.5, True, True, False, False]
        L84 = [-5.25, -10.5, False, False, True, True]
        L85 = [5.25, -10.5, False, True, True, False]
        L86 = [15.75, -10.5, True, False, False, True]
        L87 = [26.25, -10.5, True, True, False, False]
        L88 = [36.75, -10.5, True, True, False, True]
        L89 = [43.75, -10.5, False, False, True, True]


        L90 = [-43.75, -21, True, True, False, False]
        L91 = [-5.25, -21, True, True, False, True]
        L92 = [5.25, -21, True, True, False, True]
        L93 = [43.75, -21, True, False, False, True]

        self.map = [
            [ LOI(L00),     None,       LOI(L01),   None,       LOI(L02),   LOI(L03),   None,       LOI(L04),   None,       LOI(L05)],
            [ LOI(L10),     None,       LOI(L11),   LOI(L12),   LOI(L13),   LOI(L14),   LOI(L15),   LOI(L16),   None,       LOI(L17)],
            [ LOI(L20),     None,       LOI(L21),   LOI(L22),   LOI(L23),   LOI(L24),   LOI(L25),   LOI(L26),   None,       LOI(L27)],
            [ None,         None,       None,       LOI(L30),   LOI(L31),   LOI(L32),   LOI(L33),   None,       None,       None],
            [ None,         None,       LOI(L40),   LOI(L41),   None,       None,       LOI(L42),   LOI(L43),   None,       None],
            [ None,         None,       None,       LOI(L50),   None,       None,       LOI(L51),   None,       None,       None],
            [ LOI(L60),     None,       LOI(L61),   LOI(L62),   LOI(L63),   LOI(L64),   LOI(L65),   LOI(L66),   None,       LOI(L67)],
            [ LOI(L70),     LOI(L71),   LOI(L72),   LOI(L73),   LOI(L74),   LOI(L75),   LOI(L76),   LOI(L77),   LOI(L78),   LOI(L79)],
            [ LOI(L80),     LOI(L81),   LOI(L82),   LOI(L83),   LOI(L84),   LOI(L85),   LOI(L86),   LOI(L87),   LOI(L88),   LOI(L89)],
            [ LOI(L90),     None,       None,       None,       LOI(L91),   LOI(L92),   None,       None,       None,       LOI(L93)]
        ]










arena = PacBotArena()

arena.drawMap()












