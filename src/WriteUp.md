# Project: Snake 
My project has built on some additional features to the snake game provided by Udacity 


## Expected Behaviour 
When the game is first started the user will be brought to the main menu.
Here the user will see a number of options:
    - Start Game
    - Set Game Mode
    - Set Difficulty
    - Exit Game

The user can navigate menus in the application using the arrows keys on their device. 
To select an option the user can use the Enter/Return key. If the user wants to leave
a menu they can either select an option or they can press the ESC key. (NOTE: Pressing
the ESC key in the main menu or while playing the game will allow the user to exit the 
application completely)

### Start Game
Selecting the "Start Game" option in the main menu will begin the game play. Depending
on the options the user selected prior to entering the game, i.e. difficulty and game 
mode, the speed of the snake or the game board in which the user is playing on may vary.
When the user loses the snakes head will turn red. At this stage the user can press the 
ESC key and the application will be exited and the users score will be printed to the 
console.

### Set Game Mode
Selecting the "Set Game Mode" option in the main menu will bring you to a second menu.
Here you will see the options "Standard Mode" and "Walls Mode" (NOTE: Standard Mode is 
selected by default if you do not enter this menu.) When a user selects an option they
will be brought back to the main menu and their selected option will be updated accordingly. 
This can be seen in the window header. Alternatively the user can press the ESC key in 
this menu and they will brought back to the main menu without any changes to the selected 
game mode. 


If the users starts the game while in "Walls Mode" they will be brought the game where the 
edges of the game board will be surrounded by "walls". If the user's snake runs
into the "walls", then they lose the game.

### Set Difficulty
Selecting the "Set Difficulty" option in the main menu will bring you to a second menu.
Here you will see the options "Easy", "Normal" and "Hard" (NOTE: Normal is selected by 
default if you do not enter this menu.) When a user selects an option they will be 
brought back to the main menu and their selected option will be updated accordingly. 
This can be seen in the window header. Alternatively the user can press the ESC key in 
this menu and they will brought back to the main menu without any changes to the selected 
difficulty level. 


When the user starts the game, the speed of the snake will vary depending on the selected 
difficulty. The higher the difficulty, the faster the snake's speed will be initially. Also 
the increase in the snake's speed when they successfully collect some food also varies 
depending on the selectd difficulty level. Similar to before, the higher the difficulty 
level, the greater the increase in speed.

### Exit Game
Selecting the "Exit Game" option in the main menu will exit the application.


## Future Improvements and Features
Unfortunately when developing the project I came across some time constraints and was
unable to develop some features that I had originally planned on developing. Some 
additional features that I will develop in the future will be a retry menu to be 
displayed when the user loses the game and also a highscore board. I will also look 
into adding some sprites to the game to make it more colorful.


## Class Structure

The project uses 6 classes throughout. The Game class is the main controller.
It uses the other classes to carry out all the functionality of the application. 
The other classes used and their functionality are listed out below in two 
categories, Game Components and Functional Components. Game Components are classes 
used to represent objects that can be seen on the screen while playing the game. 
Functional Components are classes used to manipulate or render Game Components but 
don't actually have any visual representation themselves.

Functional Components:
- Game: the main controller class that wraps and uses all other classes
- Renderer: used to display the game and give the user a visual representation of 
            all the game components.
- Controller: used to handle user input and trigger state changes accordingly in
              the game components

Game Components:
- Snake: used to handle attributes and methods for the games playable character
- WallStructure: used to add additional obstructions to the games playable character
- GameMenu: used to handle attributes and methods of any menu in the game


## Projects Rubric

-	The project uses Object Oriented Programming techniques.

As can be seen from the wallStructure.h, wallStructure.cpp and gameMenu.h
files that I added, the project uses Object Oriented Programming techniques to group 
related functions/methods and variables/attributes into common classes that can be 
reused across the application


-	Classes use appropriate access specifiers for class members.

As seen in wallStructure.h, gameMenu.h, render.h, snake.h and 
controller.h all class data members are explicitly specified as public, 
protected, or private.


-   Class constructors utilize member initialization lists.

As seen in wallStructure.h, gameMenu.h, render.h, snake.h and 
controller.h all class members that are set to argument values 
are initialized through member initialization lists.


-   Classes abstract implementation details from their interfaces.

As seen in wallStructure.h, gameMenu.h, render.h, snake.h and 
controller.h all class member functions document their effects, 
either through function names, comments, or formal documentation. 
Member functions do not change program state in undocumented ways.


-   Classes encapsulate behavior.

As seen in wallStructure.h, gameMenu.h appropriate data and functions 
are grouped into classes. Member data that is subject to an invariant 
is hidden from the user. State is accessed via member functions.


-   Overloaded functions allow the same function to operate on different parameters.

As seen in render.h line 20 - 22 
```
void RenderMenu(GameMenu<MainMenuOptions> const menu);
void RenderMenu(GameMenu<Difficulty> const menu);
void RenderMenu(GameMenu<GameMode> const menu);
```
function are overloaded with different signatures for the same function name.


-   Templates generalize functions in the project.

As seen in gameMenu.h or in controller.h line 22 - 23
```
template <typename T>
std::string HandleMenuNavigation(GameMenu<T> &menu, int lastOptionId) const;
```
functions are declared with a template that allows it to accept a generic parameter.


-	The project accepts user input and processes the input.

As seen in controller.h and controller.cpp the HandleMenuInput and then
ultimately the HandleMenuNavigation functions accepts input from a user 
as part of the necessary operation of the program.


-	The project makes use of references in function declarations

As seen in controller.h lines 14 - 19, At least two variables are defined 
as references, or two functions use pass-by-reference in the project code.
```
void HandleMenuInput(bool &running, GameMenu<MainMenuOptions> &menu, int lastOptionId, 
                       const std::function <void(MainMenuOptions)> &selectOptionFunction) const;
```


-	The project uses destructors appropriately.

As seen in render.cpp lines 49 - 55, the project uses destructors appropriately

```
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  TTF_CloseFont(button_font);
  TTF_CloseFont(heading_font);
  TTF_Quit();
  SDL_Quit();
}
```


-	The project uses smart pointers instead of raw pointers.

As seen in game.h line 21 - 22 and game.cpp line 137 - 139 the game uses smart pointers 
to pass references of the snake and wall structures to the render and controller objects 
in the application.

```
// game.h line 21 - 22
std::shared_ptr<Snake> snake;
std::shared_ptr<WallStructure> wall_structure;

// game.cpp line 137 - 139
controller.HandleGameInput(running, snake);
UpdateGame();
renderer.RenderGame(snake, food, wall_structure);
```
