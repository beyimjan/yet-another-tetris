# Yet Another Tetris
This is a Tetris game written in C using the ncurses library.

## Installation
Binary downloads of the game can be found on [the Releases page](https://github.com/beimzhan/yet-another-tetris/releases).

To build the program, you will need `gcc`, `make` and development versions of the ncurses and c libraries installed on your system.

On Ubuntu, you can install the required packages by running the following commands:
```sh
$ sudo apt-get update
$ sudo apt-get install -y build-essential libncurses-dev libc6-dev
```

If you have these packages installed, navigate to the `src/` directory and run `make build` to build the program. Once the program has been successfully built, run `./tetris` in your terminal to start playing.

## How to Play
- Use the left arrow key to move the block left.
- Use the right arrow key to move the block right.
- Use the down arrow key to move the block down.
- Use the up arrow key to rotate the block clockwise.
- Use the space bar to rotate the block counterclockwise.

## License
This game is licensed under the GNU General Public License v3.0. See [LICENSE](LICENSE) for more information.
