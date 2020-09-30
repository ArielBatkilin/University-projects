import numpy as np
import abc
import util
import math
from game import Agent, Action


class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """

    def get_action(self, game_state):
        """
        You do not need to change this method, but you're welcome to.

        get_action chooses among the best options according to the evaluation function.

        get_action takes a game_state and returns some Action.X for some X in the set {UP, DOWN, LEFT, RIGHT, STOP}
        """

        # Collect legal moves and successor states
        legal_moves = game_state.get_agent_legal_actions()

        # Choose one of the best actions
        scores = [self.evaluation_function(game_state, action) for action in legal_moves]
        best_score = max(scores)
        best_indices = [index for index in range(len(scores)) if scores[index] == best_score]
        chosen_index = np.random.choice(best_indices)  # Pick randomly among the best

        "Add more of your code here if you want to"

        return legal_moves[chosen_index]

    def evaluation_function(self, current_game_state, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (GameState.py) and returns a number, where higher numbers are better.

        """

        # Useful information you can extract from a GameState (game_state.py)

        successor_game_state = current_game_state.generate_successor(action=action)
        c_board = current_game_state.board
        board = successor_game_state.board
        max_tile = successor_game_state.max_tile
        #weigths
        ZERO_W = 0.2
        MONO_W = 0.1
        CORNER_W = 0.8
        #added empty tiles check
        counter1 = 0
        counter2 = 0
        for i in range(4):
            for j in range(4):
                if c_board[i,j] == 0:
                    counter1 += 1
                if board[i,j] == 0:
                    counter2 += 1
        score_empty = counter2 - counter1
        #monotonic check
        score_mono = 0
        for i in range(3):
            for j in range(3):
                num1 = c_board[i, j]
                num2 = c_board[i, j + 1]
                num3 = c_board[i + 1, j]
                num4 = board[i,j]
                num5 = board[i,j+1]
                num6 = board[i+1,j]
                score_mono -= return_difference(num1,num2)
                score_mono -= return_difference(num1,num3)
                score_mono += return_difference(num4, num5)
                score_mono += return_difference(num4, num6)
        #corner count
        corner = board[3, 3]
        corner_count=0
        if(corner==max_tile):
            corner_count=+1
        my_score = score_empty*ZERO_W+ score_mono*MONO_W+corner_count*CORNER_W
        return my_score

def return_difference(num1, num2):
    if num1==0 or num2==0:
        return 0
    if num1<num2:
        return 1
    if num1==num2:
        return math.log(num1,2)
    else:
        divide = num1 / num2
        return -1 * math.log(divide,2)

def score_evaluation_function(current_game_state):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return current_game_state.score


class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinmaxAgent, AlphaBetaAgent & ExpectimaxAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evaluation_function='scoreEvaluationFunction', depth=2):
        self.evaluation_function = util.lookup(evaluation_function, globals())
        self.depth = depth

    @abc.abstractmethod
    def get_action(self, game_state):
        return


class MinmaxAgent(MultiAgentSearchAgent):

    def get_action(self, game_state):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        game_state.get_legal_actions(agent_index):
            Returns a list of legal actions for an agent
            agent_index=0 means our agent, the opponent is agent_index=1

        Action.STOP:
            The stop direction, which is always legal

        game_state.generate_successor(agent_index, action):
            Returns the successor game state after an agent takes an action
        """

        agent_index=0
        the_max = -np.inf
        actions_list=game_state.get_agent_legal_actions()
        my_action = Action.STOP
        best_action = [my_action, the_max]
        MAX_DEPTH = self.depth
        depth = 0
        for action in actions_list:
            succesor = game_state.generate_successor(0, action)
            current_action = [action, self.get_action_score_helper(depth, agent_index,succesor,MAX_DEPTH)]
            if current_action[1] > best_action[1]:
                best_action = current_action
        return best_action[0]

    def get_action_score_helper(self, depth, agent_index, game_state, MAX_DEPTH):
        actions_list = game_state.get_legal_actions(agent_index)
        if depth == MAX_DEPTH or actions_list == []:
            return self.evaluation_function(game_state)
        other = int(math.fabs(agent_index - 1))
        if agent_index == 0:
            best_action_value = -np.inf
            for action in actions_list:
                successor = game_state.generate_successor(agent_index, action)
                successor_value = self.get_action_score_helper(depth + 1, other, successor, MAX_DEPTH)
                if successor_value>best_action_value:
                    best_action_value=successor_value
            return best_action_value

        if agent_index == 1:
            best_action_value = np.inf
            for action in actions_list:
                successor = game_state.generate_successor(agent_index, action)
                successor_value = self.get_action_score_helper(depth + 1, other, successor, MAX_DEPTH)
                if successor_value < best_action_value:
                    best_action_value = successor_value
            return best_action_value



class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """
    def get_action(self, game_state):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        agent_index = 0
        alpha = -np.inf
        beta = np.inf
        alpha_beta_res = self.get_action_score_helper(game_state,
                                                      self.depth, alpha,
                                                      beta, agent_index)
        return alpha_beta_res[1]

    def get_action_score_helper(self, game_state, depth, alpha, beta, player):
        MAXPLAYER = 0
        MINPLAYER = 1
        actions_list = game_state.get_legal_actions(player)
        if depth == 0 or actions_list == []:
            return [self.evaluation_function(game_state), Action.STOP]
        if player == MAXPLAYER:
            successor_val = -np.inf
            res = [-np.inf, Action.STOP]
            for action in actions_list:
                new_game_state = game_state.generate_successor(MAXPLAYER,
                                                               action)
                successor_val = max(successor_val,
                                    self.get_action_score_helper(
                    new_game_state,
                                                               depth - 1,
                                                               alpha, beta,
                                                               MINPLAYER)[0])
                if alpha < successor_val:
                    alpha = max(alpha, successor_val)
                    res = [alpha, action]
                if beta <= alpha:
                    break
            return res
        elif player == MINPLAYER:
            successor_val = np.inf
            res = [np.inf, Action.STOP]
            for action in actions_list:
                new_game_state = game_state.generate_successor(MINPLAYER,
                                                               action)
                successor_val = min(successor_val,
                                    self.get_action_score_helper(new_game_state,
                                                               depth,
                                                               alpha, beta,
                                                               MAXPLAYER)[0])
                if beta > successor_val:
                    beta = min(beta, successor_val)
                    res = [beta, action]
                if beta <= alpha:
                    break
            return res


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
    Your expectimax agent (question 4)
    """

    def get_action(self, game_state):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        The opponent should be modeled as choosing uniformly at random from their
        legal moves.
        """
        agent_index = 0
        alpha = -np.inf
        beta = np.inf
        alpha_beta_res = self.get_action_score_helper(game_state,
                                                      self.depth, alpha,
                                                      beta, agent_index)
        return alpha_beta_res[1]

    def get_action_score_helper(self, game_state, depth, alpha, beta, player):
        MAXPLAYER = 0
        MINPLAYER = 1
        if depth == 0:
            return [self.evaluation_function(game_state), Action.STOP]

        actions_list = game_state.get_legal_actions(player)
        if actions_list == []:
            return [self.evaluation_function(game_state), Action.STOP]

        if player == MAXPLAYER:
            successor_val = -np.inf
            res = [-np.inf, Action.STOP]
            for action in actions_list:
                new_game_state = game_state.generate_successor(MAXPLAYER,
                                                               action)
                successor_val = max(successor_val,
                                    self.get_action_score_helper(
                    new_game_state,
                                                               depth - 1,
                                                               alpha, beta,
                                                               MINPLAYER)[0])
                if alpha < successor_val:
                    alpha = max(alpha, successor_val)
                    res = [alpha, action]
                if beta <= alpha:
                    break
            return res
        elif player == MINPLAYER:
            successor_val = np.inf
            res = [np.inf, Action.STOP]
            sum = 0
            probability = 1/len(actions_list)
            for action in actions_list:
                new_game_state = game_state.generate_successor(MINPLAYER,
                                                               action)
                successor_val = min(successor_val,
                                    self.get_action_score_helper(new_game_state,
                                                               depth,
                                                               alpha, beta,
                                                               MAXPLAYER)[0])
                sum += successor_val*probability
                if beta <= alpha:
                    break
            res = [sum, action]
            return res


def better_evaluation_function(current_game_state):
    """
    Your extreme 2048 evaluation function (question 5).

    DESCRIPTION: A better evaluation function for the 2048 problem
    """
    board = current_game_state.board

    #Weigths of the heuristic functions
    sum1_weigth = 4
    sum2_weigth = 3
    zerosum_weigth = 5
    corner_bonus_weigth = 10
    biggest_weigth = 3
    dif_num_weigth = 1

    #Strong monnotonic check
    sum1 = strong_monotone_check(board)

    #Weak monotonic check
    sum2=0
    for i in range(3):
        for j in range(1,3):
            num1=board[i, j]
            num2=board[i+1,j]
            if num1*num2==0:
                continue
            if num1<=num2:
                sum2+=1
            else:
                sum2-=math.log(num1/num2,2)

    #Zero chech
    zero_sum=zero_check(board)

    #Biggest in the corner
    corner_bonus = 0
    maxi = current_game_state.max_tile
    if board[3,3]==maxi:
        corner_bonus = 4
    if board[3,2]==maxi:
        corner_bonus = 2
    if board[3, 1] == maxi:
        corner_bonus = 1
    if board[3,0]==maxi:
        corner_bonus=0.5

    #Biggest tile
    biggest_bonus = math.log(maxi,2)
    #Different_nums
    num_list=[0]
    for i in range(4):
        for j in range(4):
            check_difference_numbers(board[i,j],num_list)
    dif_num = -num_list[0]


    sum = zero_sum*zerosum_weigth+corner_bonus*corner_bonus_weigth+sum1*sum1_weigth
    sum +=biggest_bonus*biggest_weigth+dif_num*dif_num_weigth + sum2*sum2_weigth

    return sum

def strong_monotone_check(board):
    sum1=0
    sum1 += num_relation(board[0, 3], board[0, 2])
    sum1 += num_relation(board[0, 2], board[0, 1])
    sum1 += num_relation(board[0, 1], board[0, 0])
    sum1 += num_relation(board[0, 0], board[1, 0])
    sum1 += num_relation(board[1, 0], board[1, 1])
    sum1 += num_relation(board[1, 1], board[1, 2])
    sum1 += num_relation(board[1, 2], board[1, 3])
    sum1 += num_relation(board[1, 3], board[2, 3])
    sum1 += num_relation(board[2, 3], board[2, 2])
    sum1 += num_relation(board[2, 2], board[2, 1])
    sum1 += num_relation(board[2, 1], board[2, 0])
    sum1 += num_relation(board[2, 0], board[3, 0])
    sum1 += num_relation(board[3, 0], board[3, 1])
    sum1 += num_relation(board[3, 1], board[3, 2])
    sum1 += num_relation(board[3, 2], board[3, 3])
    return sum1

def num_relation(num1,num2):
    if num1*num2 == 0:
        return 0
    if num2<num1:
        difference = num1/num2
        return -math.log(difference,2)
    if num1==num2:
        return 1
    if num2>num1:
        num = num2/num1
        result=1/num
        return result

def check_difference_numbers(num,list):
    if num==0:
        return
    if num not in list[1:]:
        list[0]-=2
        list.append(num)
    else:
        list[0]+=1

def zero_check(board):
    num_zero=0
    for i in range(4):
        for j in range(4):
            if board[i, j] == 0:
                num_zero += 1
    return num_zero

# Abbreviation
better = better_evaluation_function
