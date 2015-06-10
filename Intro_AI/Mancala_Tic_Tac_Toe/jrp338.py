# File: jrp338.py
# Author(s) names AND netid's: Nishant Subramani nso155, Jaiveer Kothari jvk383, Jeanette Pranin jrp338 
# Date: 4/17/15
# Defines a simple artificially intelligent player agent
# You will define the alpha-beta pruning search algorithm
# You will also define the score function in the MancalaPlayer class,
# a subclass of the Player class.


from random import *
from decimal import *
from copy import *
from MancalaBoard import *
from TicTacToe import *

# a constant
INFINITY = 1.0e400

class Player:
    """ A basic AI (or human) player """
    HUMAN = 0
    RANDOM = 1
    MINIMAX = 2
    ABPRUNE = 3
    CUSTOM = 4
    
    def __init__(self, playerNum, playerType, ply=0):
        """Initialize a Player with a playerNum (1 or 2), playerType (one of
        the constants such as HUMAN), and a ply (default is 0)."""
        self.num = playerNum
        self.opp = 2 - playerNum + 1
        self.type = playerType
        self.ply = ply

    def __repr__(self):
        """Returns a string representation of the Player."""
        return str(self.num)
        
    def minimaxMove(self, board, ply):
        """ Choose the best minimax move.  Returns (score, move) """
        move = -1
        score = -INFINITY
        turn = self
        for m in board.legalMoves(self):
            #for each legal move
            if ply == 0:
                #if we're at ply 0, we need to call our eval function & return
                return (self.score(board), m)
            if board.gameOver():
                return (-1, -1)  # Can't make a move, the game is over
            nb = deepcopy(board)
            #make a new board
            nb.makeMove(self, m)
            #try the move
            opp = Player(self.opp, self.type, self.ply)
            s = opp.minValue(nb, ply-1, turn)
            #and see what the opponent would do next
            if s > score:
                #if the result is better than our best score so far, save that move,score
                move = m
                score = s
        #return the best score and move so far
        return score, move

    def maxValue(self, board, ply, turn):
        """ Find the minimax value for the next move for this player
        at a given board configuation. Returns score."""
        if board.gameOver():
            return turn.score(board)
        score = -INFINITY
        for m in board.legalMoves(self):
            if ply == 0:
                #print "turn.score(board) in max value is: " + str(turn.score(board))
                return turn.score(board)
            # make a new player to play the other side
            opponent = Player(self.opp, self.type, self.ply)
            # Copy the board so that we don't ruin it
            nextBoard = deepcopy(board)
            nextBoard.makeMove(self, m)
            s = opponent.minValue(nextBoard, ply-1, turn)
            #print "s in maxValue is: " + str(s)
            if s > score:
                score = s
        return score
    
    def minValue(self, board, ply, turn):
        """ Find the minimax value for the next move for this player
            at a given board configuation. Returns score."""
        if board.gameOver():
            return turn.score(board)
        score = INFINITY
        for m in board.legalMoves(self):
            if ply == 0:
                #print "turn.score(board) in min Value is: " + str(turn.score(board))
                return turn.score(board)
            # make a new player to play the other side
            opponent = Player(self.opp, self.type, self.ply)
            # Copy the board so that we don't ruin it
            nextBoard = deepcopy(board)
            nextBoard.makeMove(self, m)
            s = opponent.maxValue(nextBoard, ply-1, turn)
            #print "s in minValue is: " + str(s)
            if s < score:
                score = s
        return score


    # The default player defines a very simple score function
    # You will write the score function in the MancalaPlayer below
    # to improve on this function.
    def score(self, board):
        """ Returns the score for this player given the state of the board """
        if board.hasWon(self.num):
            return 100.0
        elif board.hasWon(self.opp):
            return 0.0
        else:
            return 50.0

    # You should not modify anything before this point.
    # The code you will add to this file appears below this line.

    # You will write this function (and any helpers you need)
    # You should write the function here in its simplest form:
    #   1. Use ply to determine when to stop (when ply == 0)
    #   2. Search the moves in the order they are returned from the board's
    #       legalMoves function.
    # However, for your custom player, you may copy this function
    # and modify it so that it uses a different termination condition
    # and/or a different move search order.
    def alphaBetaMove(self, board, ply):
        """ Chooses a move with alpha beta pruning.
        Returns a move with its score value in the form (score, move) """
        #set move, score, turn, alpha, beta, and max_ply
        move = -1
        score = -INFINITY
        turn = self
        alpha = -INFINITY
        beta = INFINITY
        max_ply = 10

        #for each legal move
        for m in board.legalMoves(self):
            if ply == 0:
                #if we're at ply 0, we need to call our eval function & return
                return (self.score(board), m)
            #cannot have a ply greater than max_ply
            if ply > max_ply:
                ply = max_ply
            if board.gameOver():
                return (-1, -1)  # Can't make a move, the game is over
            nb = deepcopy(board)
            #make a new board
            nb.makeMove(self, m)
            #try the move
            opp = Player(self.opp, self.type, self.ply)
            s = opp.minValueAB(nb, ply-1, alpha, beta, turn)
            #and see what the opponent would do next
            if s > score:
                #if the result is better than our best score so far, save that move,score
                move = m
                score = s
        #return the best score and move so far
        return score, move

        
        print "Alpha Beta Move not yet implemented"
        #returns the score adn the associated moved
        return (-1,1)
    
    def maxValueAB(self, board, ply, alpha, beta, turn):
        """ Returns: the utility value for Max for AB Pruning
            Inputs: board: current state in game
                    ply: The depth to analyze
                    alpha: The value of the best alternative for Max along the path to board
                    beta: The value of the best alternative for Min along the path to board
                    turn: Which player's turn it is
        """
        if board.gameOver():
            return turn.score(board)
        v = -INFINITY
        for m in board.legalMoves(self):
            if ply == 0:
                #print "turn.score(board) in max value is: " + str(turn.score(board))
                return turn.score(board)
            
            # make a new player to play the other side
            opponent = Player(self.opp, self.type, self.ply)
            
            # Copy the board so that we don't ruin it
            nextBoard = deepcopy(board)
            
            #make the move you are currently analyzing
            nextBoard.makeMove(self, m)

            #we want v to be the largest value that our opponent could obtain through minValueAB
            v = max(v,opponent.minValueAB(nextBoard, ply-1, alpha, beta, turn))

            #Check whether v >= our current best alternative for Min
            if v >= beta:
                return v 
            alpha = max(alpha, v)
            
        #return the value of the move we will execute
        return v

    def minValueAB(self, board, ply, alpha, beta, turn):
        """ Returns: the utility value for Min for AB Pruning
            Inputs: board: current state in game
                    ply: The depth to analyze
                    alpha: The value of the best alternative for Max along the path to board
                    beta: The value of the best alternative for Min along the path to board
                    turn: Which player's turn it is
        """
        #if someone has won
        if board.gameOver():
            return turn.score(board)
        v = INFINITY
        #for every legal move
        for m in board.legalMoves(self):
            if ply == 0:
                return turn.score(board)
            
            # make a new player to play the other side
            opponent = Player(self.opp, self.type, self.ply)
            
            # Copy the board so that we don't ruin the original
            nextBoard = deepcopy(board)

            #make the move you are currently analyzing
            nextBoard.makeMove(self, m)
            
            #we want v to be the smallest value that our opponent could obtain through maxValueAB
            v = min(v,opponent.maxValueAB(nextBoard, ply-1, alpha, beta, turn))

            #Check whether v <= our current best alternative for Max
            if v <= alpha:
                return v
            beta = min(beta, v)
            
        #return the value of the move we will execute
        return v

    def chooseMove(self, board):
        """ Returns the next move that this player wants to make """
        if self.type == self.HUMAN:
            move = input("Please enter your move:")
            while not board.legalMove(self, move):
                print move, "is not valid"
                move = input( "Please enter your move" )
            return move
        elif self.type == self.RANDOM:
            move = choice(board.legalMoves(self))
            print "chose move", move
            return move
        elif self.type == self.MINIMAX:
            val, move = self.minimaxMove(board, self.ply)
            print "chose move", move, " with value", val
            return move
        elif self.type == self.ABPRUNE:
            val, move = self.alphaBetaMove(board, self.ply)
            print "chose move", move, " with value", val
            return move
        elif self.type == self.CUSTOM:
            #Implements a CUSTOM player that does AB Pruning with 10-ply
            threshold_ply = 10
            val, move = self.alphaBetaMove(board, threshold_ply)
            print "chose move", move, " with value", val
            return move
        else:
            print "Unknown player type"
            return -1


# Note, you should change the name of this player to be your netid
class jrp338(Player):
    """ Defines a player that knows how to evaluate a Mancala gameboard
    intelligently
    """

    def score(self, board):
        """ Evaluate the score of the Mancala board for this player """
        
        #gets the player's and opponent's current score in their Mancalas
        if(self.num == 1):
            player_mancala = board.scoreCups[0]
            opp_mancala = board.scoreCups[1]
        else:
            player_mancala = board.scoreCups[1]
            opp_mancala = board.scoreCups[0]
        
        #returns a weighted score as a heuristic
        return 2*(player_mancala - opp_mancala)
