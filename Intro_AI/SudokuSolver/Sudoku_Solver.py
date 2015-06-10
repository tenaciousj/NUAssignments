#!/usr/bin/env python

#Team: NapperHackers
#Members: Jeanette Pranin (jrp338), Jaiveer Kothari (jvk383), Nishant Subramani (nso155)
import struct, string, math, copy, time

num_assignments = 0

class SudokuBoard:
    """This will be the sudoku board game object your player will manipulate."""
  
    def __init__(self, size, board):
      """the constructor for the SudokuBoard"""
      self.BoardSize = size #the size of the board
      self.CurrentGameBoard= board #the current state of the game board

    def set_value(self, row, col, value):
        """This function will create a new sudoku board object with the input
        value placed on the GameBoard row and col are both zero-indexed"""

        #add the value to the appropriate position on the board
        self.CurrentGameBoard[row][col]=value
        #return a new board of the same size with the value added
        return SudokuBoard(self.BoardSize, self.CurrentGameBoard)
                                                                  
                                                                  
    def print_board(self):
        """Prints the current game board. Leaves unassigned spots blank."""
        div = int(math.sqrt(self.BoardSize))
        dash = ""
        space = ""
        line = "+"
        sep = "|"
        for i in range(div):
            dash += "----"
            space += "    "
        for i in range(div):
            line += dash + "+"
            sep += space + "|"
        for i in range(-1, self.BoardSize):
            if i != -1:
                print "|",
                for j in range(self.BoardSize):
                    if self.CurrentGameBoard[i][j] > 9:
                        print self.CurrentGameBoard[i][j],
                    elif self.CurrentGameBoard[i][j] > 0:
                        print "", self.CurrentGameBoard[i][j],
                    else:
                        print "  ",
                    if (j+1 != self.BoardSize):
                        if ((j+1)//div != j/div):
                            print "|",
                        else:
                            print "",
                    else:
                        print "|"
            if ((i+1)//div != i/div):
                print line
            else:
                print sep

def parse_file(filename):
    """Parses a sudoku text file into a BoardSize, and a 2d array which holds
    the value of each cell. Array elements holding a 0 are considered to be
    empty."""

    f = open(filename, 'r')
    BoardSize = int( f.readline())
    NumVals = int(f.readline())

    #initialize a blank board
    board= [ [ 0 for i in range(BoardSize) ] for j in range(BoardSize) ]

    #populate the board with initial values
    for i in range(NumVals):
        line = f.readline()
        chars = line.split()
        row = int(chars[0])
        col = int(chars[1])
        val = int(chars[2])
        board[row-1][col-1]=val
    
    return board
    
def is_complete(sudoku_board):
    """Takes in a sudoku board and tests to see if it has been filled in
    correctly."""
    BoardArray = sudoku_board.CurrentGameBoard
    size = len(BoardArray)
    subsquare = int(math.sqrt(size))

    #check each cell on the board for a 0, or if the value of the cell
    #is present elsewhere within the same row, column, or square
    for row in range(size):
        for col in range(size):
            if BoardArray[row][col]==0:
                return False
            for i in range(size):
                if ((BoardArray[row][i] == BoardArray[row][col]) and i != col):
                    return False
                if ((BoardArray[i][col] == BoardArray[row][col]) and i != row):
                    return False
            #determine which square the cell is in
            SquareRow = row // subsquare
            SquareCol = col // subsquare
            for i in range(subsquare):
                for j in range(subsquare):
                    if((BoardArray[SquareRow*subsquare+i][SquareCol*subsquare+j]
                            == BoardArray[row][col])
                        and (SquareRow*subsquare + i != row)
                        and (SquareCol*subsquare + j != col)):
                            return False
    return True

def init_board(file_name):
    """Creates a SudokuBoard object initialized with values from a text file"""
    board = parse_file(file_name)
    return SudokuBoard(len(board), board)



########################################OUR CODE########################################

def solve(initial_board, forward_checking = False, MRV = False, MCV = False,
    LCV = False):
    """Takes an initial SudokuBoard and solves it using back tracking, and zero
    or more of the heuristics and constraint propagation methods (determined by
    arguments). Returns the resulting board solution. """

    #starts the time to compute how long solving will take
    start = time.clock()

    #keeps track of how many assignments the function makes
    global num_assignments

    #sets domains to iterate through based on which heuristics are on
    domains = SetDomains(initial_board, forward_checking, MRV, MCV, LCV)    

    #Solve Sudoku!
    result = SolveSudoku(initial_board, domains, forward_checking, MRV, MCV, LCV)
    
    if result == False:
        print "No Solution exists"

    #print "Num assignments: " + str(num_assignments)
    num_assignments = 0
    end = time.clock()
    #print "Time taken: " + str(end-start)
    return result


def SolveSudoku(initial_board, domains, forward_checking, MRV, MCV,
    LCV):
    """Solves the sudoku board
    """

    global num_assignments

    #if the board is complete, the puzzle is solved
    if is_complete(initial_board):
        return initial_board

    #set the initial position to check (will be reset if one of the heuristics is on)
    row = 0
    col = 0

    #Gets current game board state in array form
    BoardArray = initial_board.CurrentGameBoard
    size = len(BoardArray)

    #Choose the unassigned location to try values in
    row, col = ChooseUnassignedLocation(BoardArray, domains, forward_checking, MRV, MCV, LCV)

    #if there is no row or col, then there are no unassigned locations and the puzzle is solved
    if row == None:
        return initial_board
    
    #if LCV is on, create LCV list
    if LCV:
        iteration_list=LCV_list(BoardArray,domains)

    #otherwise, we will iterate through the domains of the position
    else:
        iteration_list=domains[row][col]
    
    if type(iteration_list) is list and type(iteration_list) is list:
        for num in iteration_list:

            #if forward checking is not on, we have to check whether the value is safe
            #if LCV is on, we have to check whether the value is safe
            #if forward checking is on, we have already performed isSafe, so no need to check again
            if (not forward_checking and isSafe(BoardArray,row,col,num)) or (LCV and isSafe(BoardArray,row,col,num)) or (forward_checking and not LCV):

                #keep a deep copy of the board
                copied_board = copy.deepcopy(initial_board)

                #tentatively set the value
                copied_board.set_value(row,col,num)
                #add this assignment to total count
                num_assignments+=1

                #keep a deep copy of the current domain set
                copied_domains = copy.deepcopy(domains)
                
                #propogate constraints forward
                if forward_checking:
                    copied_domains = ForwardChecking(initial_board, copied_domains, row, col, num)

                #try to solve Sudoku
                result = SolveSudoku(copied_board, copied_domains, forward_checking, MRV, MCV, LCV)

                #if you solved it, then return the final board
                if result:
                    return result
                

    #No solution exists
    return False

def LCV_list(boardArr,domains):
    """returns list of values sorted from the value involved in the least amount of constraints
        to the value involved in the most amount
    """
    size = len(boardArr)
    least_pop_val=1
    val_counter=0

    #dictionary that keeps track of how many times a value appears in a neighboring cell's domain
    val_dict={x:0 for x in range(1,size+1)}

    for key in val_dict:
        for i in range(size): # rows
            for j in range(size): # cols 
                
                
                if type(domains[i][j]) is not bool and key in domains[i][j]:
                    val_dict[key]+=1

    #sort from least involved to most involved
    ordered = sorted(val_dict, key=val_dict.get)

    return ordered



def ForwardChecking(board, domains, row, col, num):
    """Reduces the domain of position (row, col) based on what values are legal
    Makes the SolveSudoku function iterate through less values and save time
    """
    BoardArray = board.CurrentGameBoard
    size = len(BoardArray)

    #helper variables for checking the box
    mod = int(math.sqrt(len(BoardArray)))
    boxStartRow = row-row%mod
    boxStartCol = col-col%mod
    
    #checking the row
    for k in range(size):
        if type(domains[row][k]) is list:
            for el in domains[row][k]:
                if el==num:
                    domains[row][k].remove(el)
                

    #checking the col
    for l in range(size):
        if type(domains[l][col]) is list:
            for el in domains[l][col]:
                if el==num:
                    domains[l][col].remove(el)

    #checking box                                                                  
    subsquare = int(math.sqrt(size))
    for i in range(subsquare):
        for j in range(subsquare):
            if type(domains[i+boxStartRow][j+boxStartCol]) is list:
                for el in domains[i+boxStartRow][j+boxStartCol]:
                    if el==num:
                        domains[i+boxStartRow][j+boxStartCol].remove(el)

    #return the shortened domains                                                                 
    return domains                                                                           


def SetDomains(initial_board, forward_checking, MRV, MCV, LCV):
    """Sets the domains of each cell in the board based on which heuristics are on
    """
    BoardArray=initial_board.CurrentGameBoard

    size = len(BoardArray)

    #makes an empty nested array
    BoardDomain = [[[0 for _ in range(size)] for _ in range(size)] for _ in range(size)]

    for i in range(size):
        for j in range(size):
            BoardDomain[i][j]=[]
            if BoardArray[i][j]==0:
                for num in range(1,size+1):
                    #if forward checking is on, check if it's a safe value
                    if forward_checking:
                        if isSafe(BoardArray,i,j,num):
                            BoardDomain[i][j].append(num)
                    #otherwise, backtracking only
                    else:
                        BoardDomain[i][j].append(num)
            #if the value is a preset value from the board, keep it as a True so it is not mutable
            else:
               BoardDomain[i][j] = True 

    return BoardDomain
    
    
def isSafe(boardArr, row, col, num):
    """Checks whether a value is safe by checking whether the value appears in the same row, col, or box
    """
    if UsedInRow(boardArr,row,num) or UsedInCol(boardArr,col,num) or UsedInBox(boardArr, row-row%int(math.sqrt(len(boardArr))), col-col%int(math.sqrt(len(boardArr))), num):
        return False
    else:
        return True

def UsedInRow(boardArr, row, num):
    """Checks whether a value num has been used in row
    """
    size = len(boardArr)
    for col in range(size):
        if boardArr[row][col] == num:
            return True
    return False

def UsedInCol(boardArr, col, num):
    """Checks whether a value num has been used in col
    """
    size = len(boardArr)
    for row in range(size):
        if boardArr[row][col] == num:
            return True
    return False

def UsedInBox(boardArr,boxStartRow,boxStartCol,num):
    """Checks whether a value num has been used in the corresponding box
    """
    size = len(boardArr)
    subsquare = int(math.sqrt(size))
    for i in range(subsquare):
        for j in range(subsquare):
            if boardArr[i+boxStartRow][j+boxStartCol]==num:
                return True
    return False

def MCVHelper(boardArr, domains, row, col):
    """Helper function for MCVHelper that counts the number of constraints of each cell
    """

    size = len(boardArr)
    subsquare = int(math.sqrt(size))
    row_of_square = row // subsquare
    col_of_square = col //subsquare
    

    num_constraints = 0

    for i in range(size):
        if boardArr[row][i] == 0:
            num_constraints+=1
        if boardArr[i][col] == 0:
            num_constraints+=1
    for j in range(row_of_square*subsquare, (row_of_square+1)*subsquare):
        for k in range(col_of_square*subsquare, (col_of_square+1)*subsquare):
            #make sure to not double count cells we've already visited
            if j != row or k != col:
                if boardArr[j][k] == 0:
                    num_constraints+=1
    return num_constraints
 



def ChooseUnassignedLocation(boardArr, domains, forward_checking, MRV, MCV, LCV):
    
    """Chooses an unassigned location to try values in based on which heuristics are on
    """
    size = len(boardArr)
    
    #MRV = choose the variable with the fewest values left
    if forward_checking and MRV:
        min_row = 0
        min_col = 0
        min_len = 10000
        for row in range(size):
            for col in range(size):
                if boardArr[row][col] == 0 and type(domains[row][col]) is list and 0 < len(domains[row][col]) < min_len:
                    min_len = len(domains[row][col])
                    min_row = row
                    min_col = col
                    #1 is the shortest a valid list can be
                    if min_len == 1:
                        break
        
        return min_row, min_col       

    #MCV = choose the variable that is involved in the largest number of constraints with unassigned variables
    if forward_checking and MCV:
        max_num_constraints = -1
        max_row = -1
        max_col = -1

        for row in range(size):
            for col in range(size):
                if type(domains[row][col]) is list and boardArr[row][col] == 0: #and len(domains[row][col]) > 0
                    #print "len " + str(len(domains[row][col]))

                    num_constraints = MCVHelper(boardArr, domains, row, col)
                    #print "[" + str(row) + ", " + str(col) + "], " + str(num_constraints) + " num_constraints"
                    if num_constraints > max_num_constraints:
                        #print str(row) + " row, " + str(col) + " col, " + " THIS ONE CHOSEN"
                        max_num_constraints = num_constraints
                        max_row = row
                        max_col = col
        return max_row, max_col
        
    #otherwise, just backtracking with maybe forward checking, return the first unassigned location you find
    else:
        size = len(boardArr)
        for row in range(size):
            for col in range(size):
                if boardArr[row][col] == 0:
                    return row, col
    return None, None

