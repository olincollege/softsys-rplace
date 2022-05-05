# `r/place`: a terminal-based multiplayer interactive canvas
### Chris Allum, Maya Sivanandan, Berwin Lan

## Objectives
We were inspired by the subreddit `r/place`, which was a canvas where users could click on a pixel and change its color every 5 minutes. The goal of our project was to use networking and the `ncurses` library for the GUI to recreate this functionality on a much smaller and more basic canvas. For our lower bound, we are creating an interface where a client can connect to a server and use arrow keys to fill pixels. Additional goals include multiple clients connecting and editing the canvas, a 5-minute timer, and using the mouse cursor instead of arrow keys to select pixels and colors.

## Learning Goals
Our learning goals at the start of the project were the following:
* working with threading and semaphores
    * We did not center this goal in the scope of our project. One area we could have used threading is in handling multiple clients, which is supposedly better for scaling and preventing deadlocks.
* more advanced networking than both our Project 1s
    * This is where a bulk of our time went. We were more advanced in both the number of clients the program could handle and the kind of data being sent over the network. With `r/place`, multiple clients can play at once, and we are sending different types of data over the network based on multiple input modes.
* an interactive and engaging project
    * We hope that it is engaging! We focused a lot on the GUI and making it simple to use and interact with.

## Outcomes
TODO w/ screenshots!

* Each client has a `PlayerState` struct with the following attributes:
    * `grid` represents an `M` by `N` pixel canvas
    * `loc_x` and `loc_y` represent the cursor coordinates
    * `color` stores the color the player currently has selected
    * `locked` is a boolean state representing a time limit for placing pixels
* The `game_state` variable is an array representing an `M` by `N` canvas of the same dimensions as the `PlayerState` `grid`.

```c
This is an example code block
```

### Networking
We have one server that forks when a new client joins. When any one client adds a pixel to the canvas, the new pixel's coordinates and color is sent to the server. The server can send it to all the other clients, and client-side, the graphics are updated according to the new information received. 

We made the design decisions to only send updates from clients and to render all graphics on the client-side for better efficiency and clarity. A large part of this was because we wanted to limit the amount of data being sent over the network in order to minimize the need to pack data in space-efficient modes and the risk of data loss. For example, instead of sending entire board states consisting of `M`*`N` values, we chose to only send single pixels that were changed by a client, which vastly decreases the amount of data that gets sent over the network. Based on this, we

We have tested our networking across multiple machines on the same WiFi network without any issues! If you are running our code on a single machine, it is also able to run with multiple shells.

### GUI
We used mouse functionality from the `ncurses` library for the user's pixel location selection, and we used the left and right arrow keys to select the color. The client can move their cursor around the canvas, and the box beneath the cursor will be highlighted in the color they select. The graphics are initialized when the client first connects to the server, and all graphics up to this process are handled solely on the client-side (no information is exchanged with the server). The client double-taps the `ENTER` key to lock in the pixel they have selected with a specific location and color, and that data is sent to the server (and other clients) using the process described under [Networking](#markdown-header-networking).

The server does not have a GUI, as its core functionality is to handle client data.

### Remaining work
At time of submission, the 

## Resources
* Chapters 10 and 11 in Griffiths, D. (2012). Head First C. O’Reilly Media.
    * These chapters had to do with forking and networking, respectively.
* We found [Beej's guide to network programming](https://beej.us/guide/bgnet/) extremely helpful for all things related to networking and sockets.
* `ncurses` documentation
    * [Sample `ncurses` code](http://www.paulgriffiths.net/program/c/curses.php)
* StackOverflow