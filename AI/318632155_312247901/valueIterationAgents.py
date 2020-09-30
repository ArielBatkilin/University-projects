# valueIterationAgents.py
# -----------------------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

import mdp, util

from learningAgents import ValueEstimationAgent

class ValueIterationAgent(ValueEstimationAgent):
  """
      * Please read learningAgents.py before reading this.*

      A ValueIterationAgent takes a Markov decision process
      (see mdp.py) on initialization and runs value iteration
      for a given number of iterations using the supplied
      discount factor.
  """
  def __init__(self, mdp, discount = 0.9, iterations = 100):
    """
      Your value iteration agent should take an mdp on
      construction, run the indicated number of iterations
      and then act according to the resulting policy.
    
      Some useful mdp methods you will use:
          mdp.getStates()
          mdp.getPossibleActions(state)
          mdp.getTransitionStatesAndProbs(state, action)
          mdp.getReward(state, action, nextState)
    """
    self.mdp = mdp
    self.discount = discount
    self.iterations = iterations
    self.values = util.Counter() # A Counter is a dict with default 0

    for i in range(iterations):
        new_values = self.values.copy()
        for state in self.mdp.getStates():
            best_action = float('-inf')
            poss_actions = self.mdp.getPossibleActions(state)
            for action in poss_actions:
                trans_probs = self.mdp.getTransitionStatesAndProbs(state,
                                                                   action)
                action_val = 0
                for tuple in trans_probs:
                    action_val += self.values[tuple[0]]*tuple[1]
                if action_val > best_action:
                    best_action = action_val
            new_values[state] = self.mdp.getReward(state, None, None)
            if len(poss_actions) != 0:
                new_values[state] += self.discount*best_action
        self.values = new_values.copy()

  def getValue(self, state):
    """
      Return the value of the state (computed in __init__).
    """
    return self.values[state]

  def getQValue(self, state, action):
    """
      The q-value of the state action pair
      (after the indicated number of value iteration
      passes).  Note that value iteration does not
      necessarily create this quantity and you may have
      to derive it on the fly.
    """
    trans_probs = self.mdp.getTransitionStatesAndProbs(state, action)
    action_val = 0
    for tuple in trans_probs:
        action_val += tuple[1]*(self.discount*self.values[tuple[0]] +
                                self.mdp.getReward(state, action, tuple[0]))
    return action_val

  def getPolicy(self, state):
    """
      The policy is the best action in the given state
      according to the values computed by value iteration.
      You may break ties any way you see fit.  Note that if
      there are no legal actions, which is the case at the
      terminal state, you should return None.
    """
    poss_actions = self.mdp.getPossibleActions(state)
    if len(poss_actions) == 0:
        return None
    else:
        best_action = poss_actions[0]
        best_action_val = float('-inf')
        for action in poss_actions:
            action_val = self.getQValue(state, action)
            if action_val > best_action_val:
                best_action_val = action_val
                best_action = action
        return best_action

  def getAction(self, state):
    "Returns the policy at the state (no exploration)."
    return self.getPolicy(state)
  
