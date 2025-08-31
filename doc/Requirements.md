# Sokoban Game Requirements
## Functional Requirements
### Game Board
Display a grid-based board with walls, floors, boxes, and goal locations.  
Load game boards from level files.  
### Player Controls
Move up, down, left, and right using keyboard or controller input.  
Support reverse, undo, and pull actions.  
Prevent movement through walls and restrict pushing more than one box at a time.  
### Box Mechanics
Allow the player to push boxes onto goal locations.  
Detect when all boxes are on goals (level complete).  
### Levels
Load levels from external files, built-in data, or a web server.  
Support multiple levels and level selection.  
### User Interface
Display the current level, moves counter, and restart option.  
Show win/lose messages.  
Provide level selection and editor screens.  
Allow restarting or selecting a new level.  
## Non-Functional Requirements
### Performance
The game should run smoothly on modern desktop systems.  
### Portability
Support Linux and Windows. Optional: Raspberry Pi (RPi).  
### Extensibility
Undo functionality  
Sound effects  
Solver  
Level editor  
Level generator  
Special boxes (e.g., rolling boxes, squashable boxes)  
Hazards  
Time limit  
External controller support  
### Documentation
Provide clear instructions for building, running, and playing the game.


 