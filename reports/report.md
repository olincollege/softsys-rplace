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
### Networking
* one server that connects to all the clients and centralizes any information from clients and updates them
* Using signal to evaluate multiple simultanious clients
* If a client joins part way throgh the game, the server will automatically provide them the most recent version of the board so that everyone is always shown the same thing, no matter when you join.

###
* Whenever the server detects the one of the clients has pushed a change, it creates a new thread to assess what has changed. The reason that we are using threads is that reading from a socket can potentially take a very long time. Whenever one reads from a socket, if it cannot read the data immedietly, it will block the process. Because we still needed different processes to run while checking for updates, we needed to use threads. 
* We originally tried to use forking. However, we ran into a ton of difficulty sharing data between the child and parent processes. We therefore swiched to multiple threads.

### GUI
* server doesn't have a GUI, its only role is to do updates and host clients
* client's initial interface is a blank canvas
* use cursor to select pixel location, stdin to select color by number, enter to place pixel
    * info is sent to server
* GUI automatically updates when stuff is sent from the server


## Resources
* Chapter 11 in Griffiths, D. (2012). Head First C. O’Reilly Media.
* We found [Beej's guide to network programming](https://beej.us/guide/bgnet/) extremely helpful for all things related to networking and sockets.
* `ncurses` documentation
    * [Sample `ncurses` code](http://www.paulgriffiths.net/program/c/curses.php)