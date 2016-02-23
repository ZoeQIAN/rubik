# RUBIK CUBE

### Welcom Page 
#### The buttons are (from the top to bottom):
Start
Scores
Quit

#### If you click on "Start", it transits to the page for choosing game level.
From the top to bottom:
Simple
Medium
Hard
Click either level, the rubik cube game starts

#### Game Mode
use left button to turn the rubik around
use right button to rotate the cubes of the rubik


### Structures

#### Constant and enum variables
Decalaration in param.h

#### Matrix/vector functions
basicfunction.h cut from Camera.cpp

#### GameController
  - Member variables:
    - Accueil: Buttons
    - Niveau: Buttons
    - Scores: Display the file of scores
    - Game: Rubik rubik
  - Member functions
    - Render: render the different elements according to the Mode (accueil, niveau, scores, game)
      - in the game mode, call the render of rubik rubik->Render()
    - mouseClick(), mouseRelease, mouseMove : mouse events
