import numpy as np

def redTarget(pacX, pacY, ghoX, ghoY, state):
    if str(state) not "F":
        return np.array([pacX, pacY])
    else:
        return np.array([1, 1])
    
def orangeTarget(pacX, pacY, ghoX, ghoY, state):
    if str(state) not "F":
        if (abs(pacX - ghoX) + abs(pacY - ghoY)) > 8:
            return np.array([pacX, pacY])
        else:
            return np.array([1, 1])
    else:
        return np.array([1, 1])