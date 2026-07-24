Description
A-Maze-ing is a Python project that generates random mazes from a configuration file. Depending on the selected mode, the program can generate either:

A perfect maze, where there is exactly one unique path between the entrance and the exit.
A playable maze designed for a Pac-Man-like game, containing loops and multiple alternative routes while remaining fully connected.
The project reads a configuration file, generates the maze using a randomized algorithm, computes the shortest solution, saves the maze using a hexadecimal wall encoding, and provides a visual representation in the terminal.

The maze generator has also been designed as a reusable Python package that can be imported into future projects.

Features
Random maze generation
Reproducible mazes using a seed
Perfect and non-perfect generation modes
Automatic shortest path calculation
ASCII terminal visualization
Show/Hide shortest path
Regenerate mazes without restarting the application
Configurable wall colors
Export to hexadecimal format
Reusable Python package
Instructions
Requirements
Python 3.10+
flake8
mypy
Install dependencies:

make install

Run the project:

make run

or

python3 a_maze_ing.py config.txt

Debug mode:

make debug

Run static analysis:

make lint

Strict analysis:

make lint-strict

Clean cache files:

make clean

Configuration File
The program receives a configuration file containing one KEY=VALUE pair per line.

Example:

WIDTH=20
HEIGHT=15
ENTRY=0,0
EXIT=19,14
OUTPUT_FILE=maze.txt
PERFECT=False
SEED=42

Configuration Keys
Key	Description
WIDTH	Maze width
HEIGHT	Maze height
ENTRY	Entry coordinates (x,y)
EXIT	Exit coordinates (x,y)
OUTPUT_FILE	Output filename
PERFECT	Generates a perfect maze when True
SEED	Optional random seed

Lines beginning with # are ignored.

Example:

# Example configuration

WIDTH=30
HEIGHT=20
ENTRY=0,0
EXIT=29,19
OUTPUT_FILE=maze.txt
PERFECT=True
SEED=12345

Maze Generation Algorithm
The maze is generated using the Recursive Backtracker algorithm (Depth-First Search).

Algorithm overview:

Start from a random cell.
Mark it as visited.
Randomly select one unvisited neighbour.
Remove the wall between both cells.
Continue recursively until every cell has been visited.
Backtrack whenever a dead end is reached.
When PERFECT=True, this algorithm naturally generates a perfect maze because every cell belongs to a spanning tree.

When PERFECT=False, additional walls are removed after generation in order to:

create loops,
reduce dead ends,
provide multiple independent routes,
preserve full connectivity.
Why This Algorithm?
The Recursive Backtracker was chosen because:

it is simple to understand and implement;
it guarantees a perfect maze;
it is fast (O(width × height));
it produces long and interesting corridors;
it can easily be adapted to generate non-perfect mazes by removing additional walls.
Output File Format
The maze is stored using hexadecimal values.

Each hexadecimal digit represents the walls surrounding one cell.

Bit	Direction
0	North
1	East
2	South
3	West

A value of 1 means the wall exists.

Example:

A

Binary:

1010

Means:

North → open
East → closed
South → open
West → closed
After the maze grid, the output file contains:

Entry coordinates
Exit coordinates
Shortest path using:
N
E
S
W

Visual Representation
The maze is displayed directly in the terminal using ASCII characters.

Available interactions:

Generate a new maze
Show the solution
Hide the solution
Change wall colors
The display highlights:

walls
entrance
exit
shortest path
Reusable Module
The maze generator is implemented as a standalone class:

MazeGenerator

Example:

from mazegen import MazeGenerator

maze = MazeGenerator(
    width=20,
    height=15,
    seed=42,
    perfect=True
)

maze.generate()

solution = maze.solve()

grid = maze.grid

The reusable package provides:

maze generation
maze solving
access to cells
access to walls
access to the shortest path
The package can be built using standard Python packaging tools and installed with:

pip install mazegen-*.whl

Project Structure
.
├── a_maze_ing.py
├── config.txt
├── Makefile
├── README.md
├── LICENSE.md
├── mazegen/
│   ├── __init__.py
│   ├── generator.py
│   ├── solver.py
│   └── cell.py
└── output/

Team Organization
Roles
<login1>
Project architecture
Maze generation
Documentation
<login2>
Visualization
Configuration parser
Tests
Planning
Initial planning:

Configuration parser
Maze generator
Solver
Export
Visualization
Documentation
During development we adjusted the schedule to first finish the generator before implementing visualization. This allowed easier testing and debugging.

Retrospective
What worked well
Good task separation.
Modular code.
Continuous testing.
Frequent Git commits.
What could be improved
Better early planning for visualization.
More automated tests.
More extensive documentation.
Tools Used
Python 3
Git
GitHub
VS Code
flake8
mypy
pytest
Resources
Documentation:

Python Documentation
PEP 8
PEP 257
typing documentation
mypy documentation
flake8 documentation
Maze algorithms:

Recursive Backtracker
Depth-First Search
Graph Theory
Spanning Trees
References:

https://docs.python.org/
https://flake8.pycqa.org/
https://mypy.readthedocs.io/
https://en.wikipedia.org/wiki/Maze_generation_algorithm
AI Usage
Artificial Intelligence was used as a development assistant for:

brainstorming project architecture;
explaining maze generation algorithms;
improving documentation;
reviewing code style;
generating README drafts.
All generated content was reviewed, understood, tested, and adapted before being included in the final project.

License
This project is distributed under the terms described in LICENSE.md.

The reusable maze generator may be reused and redistributed according to that license.

Puedes personalizar este README con capturas de pantalla del laberinto, ejemplos de salida o una sección de "Usage" más detallada si añadís funcionalidades extra.