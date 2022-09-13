# `r/place`: a terminal-based multiplayer interactive canvas
### Chris Allum, Maya Sivanandan, Berwin Lan

## Objectives
We were inspired by the subreddit `r/place`, which was a canvas where users could click on a pixel and change its color every 5 minutes. The goal of our project was to use networking and the `ncurses` library for the GUI to recreate this functionality on a much smaller and more basic canvas. For our lower bound, we are creating an interface where a client can connect to a server and use arrow keys to fill pixels. Additional goals include multiple clients connecting and editing the canvas, a 5-minute timer, and using the mouse cursor instead of arrow keys to select pixels and colors.

## Learning Goals
Our learning goals at the start of the project were the following:
* working with threading and semaphores
    * We did not center this goal in the scope of our project as we instead chose to use select() to handle the multiple clients, as this is better for handling a large number of clients with minimal risk of deadlocks.
* more advanced networking than both our Project 1s
    * This is where a bulk of our time went. We were more advanced in both the number of clients the program could handle and the kind of data being sent over the network. With `r/place`, multiple clients can play at once, and we are sending different types of data over the network based on multiple input modes.
* an interactive and engaging project
    * We hope that it is engaging! We focused a lot on the GUI and making it simple to use and interact with.

## Outcomes

```c
typedef struct {
    int grid[N_ROWS][N_COLS/2];
    int loc_x;
    int loc_y;
    int color;
    int locked;
} PlayerState;
```
* Each client has a `PlayerState` struct with the following attributes:
    * `grid` represents an `M` by `N` pixel canvas
    * `loc_x` and `loc_y` represent the cursor coordinates
    * `color` stores the color the player currently has selected
    * `locked` is a boolean state of whether or not a player can draw a pixel, which is based on an alarm timer
* The `game_state` variable is an array representing an `M` by `N` canvas of the same dimensions as the `PlayerState` `grid`.

### Networking
We have one server that forks when a new client joins. When any of the clients adds a pixel to the canvas, the new pixel's coordinates and color is sent to the server. 
```c
// Initialize an array to store relevant data
int pixel_array_out[3];

// Get coordinate and color attributes from current player's state
pixel_array_out[0] = player_state->loc_y;
pixel_array_out[1] = player_state->loc_x;
pixel_array_out[2] = player_state->color;

// Send relevant data over the network
send(server_sock, pixel_array_out, (sizeof(pixel_array_out)), 0);
```
The server can send it to all the other clients, and client-side, the graphics are updated according to the new information received. Besides any initialization, this is the only data that needs to be passed over the network between the server and clients.

We made the design decisions to only send pixel updates from clients and to render all graphics on the client-side for better efficiency and clarity. A large part of this was because we wanted to limit the amount of data being sent over the network in order to minimize the need to pack data in space-efficient modes and the risk of data loss. For example, instead of sending entire board states consisting of `M`*`N` values, we chose to only send single pixels that were changed by a client, which vastly decreases the amount of data that gets sent over the network. Furthermore, paring down the data being sent enables us to use a more elaborate and complex GUI. Since sending the full amount of information to recreate the whole GUI on every `send`/`recv` is impractical, focusing on only the changes being made allows us to keep our fancier GUI.

We have tested our networking across multiple machines on the same WiFi network without any issues! If you are running our code on a single machine, it is also able to run with multiple shells.

### GUI
![](img/canvas.png)
_An example of a blank, initialized canvas when a client first joins. As the user moves their cursor around, a pixel appears in their cursor location. They can use the left and right arrow keys to select a color._

We used mouse functionality from the `ncurses` library for the user's pixel location selection.
```c
void get_mouse_loc(int ch, int* loc)
{
    MEVENT event;
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        loc[0] = event.x;
        loc[1] = event.y;
      }
    }   
}
```
The above code is a function for getting the location of the mouse in coordinates. `MEVENT` is a mouse event, which has the `x` and `y` attributes to represent the x- and y-coordinates of the cursor. We mapped these values over to the canvas in order to accurately place the pixel in the same location as the mouse.

We used the left and right arrow keys for color selection. The client can move their cursor around the canvas, and the box beneath the cursor will be highlighted in the color they select (as seen in the image at the top of [this section](#gui)). The graphics are initialized when the client first connects to the server, and all graphics up to this process are handled solely on the client-side (no information is exchanged with the server). The client double-taps the `ENTER` key to lock in the pixel they have selected with a specific location and color, and that data is sent to the server (and other clients) using the process described under [Networking](#networking). Because drawing a pixel locks the client for 10 seconds, they need to wait for an unlock before drawing another pixel. During this cooldown period, they can still move the cursor about the canvas and use colors to preview their pixel placement.

The server does not have a GUI, as its core functionality is to handle client data and networking.

## Remaining work [ISSUE RESOLVED]
At time of submission, when the server accepts a new client, it is only able to initialize it to a blank canvas (instead of preserving any changes made to the canvas by other clients before the newest client had joined). For example, if three clients join a server, and then any one of the clients draws a pixel on the canvas, that change will be shown on all three of the clients. However, if a fourth client joins after that pixel is drawn, their canvas will not show the new pixel. We are fairly sure that this is because global variables like `game_state` that are modified in forked child processes will not get changed in the main process because forked processes live in a different segment of memory. As of most recently, we are trying to use threading to fix this.

## Remaining work [UPDATE]
As of the morning after the submission deadline, all issues have been resolved! We have fixed issues with how the forking child processes access the global memory. As a result, all new pixels that have been changing are stored properly, and any new computer that join are properly receiving the most recent version of the board. In it's current state, our project is fully functional. Multiple computers can join the game, either via the network or via multiple terminals on the host computer via local host. Each instance of the client is able to view changes to the board in realtime and is able to push changes. 

## Dependencies
If you are running our code, we used the following external libraries that you will need to install on your own machine:
* `xdotool`
* `curses` and `ncurses`

You can run the following line in your terminal to install them.
```shell
sudo apt-get install xdotool libncurses5-dev libncursesw5-dev
```

We recommend running in Linux instead of WSL, which was very inconsistent with `xdotool`. You shouldn't need GWSL, since `ncurses` uses ASCII and runs in-terminal.


## Resources
* Chapters 10, 11, and 12 in Griffiths, D. (2012). Head First C. O’Reilly Media.
    * These chapters had to do with forking, networking, and threading, respectively.
* We found [Beej's guide to network programming](https://beej.us/guide/bgnet/) extremely helpful for all things related to networking and sockets.
* `ncurses` documentation
    * [Sample `ncurses` code](http://www.paulgriffiths.net/program/c/curses.php)
* StackOverflow
