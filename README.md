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
On the right:
Back
Click either level, the rubik cube game starts

####If you click on "Scores", it transits to the page for scores of history
Not implemented yet

####If you click on "Quit", the programme will exit



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
