# `r/place`
## Chris Allum, Maya Sivanandan, Berwin Lan

### Project Goals
We were inspired by the subreddit `r/place`, which was a canvas where users could click on a pixel and change its color every 5 minutes. We plan on using networking and the `ncurses` library for the GUI to recreate this functionality on a much smaller and more basic canvas. For our lower bound, we are creating an interface where a client can connect to a server and use arrow keys to fill pixels. Additional goals include multiple clients connecting and editing the canvas, a 5-minute timer, and using the mouse cursor instead of arrow keys to select pixels and colors.

### Learning Goals
* working with threading and semaphores
* more advanced networking than both our Project 1s
* an interactive and engaging project

### Project Resources
* Chapter 11 in Griffiths, D. (2012). Head First C. O’Reilly Media.
* [Beej's guide to network programming](https://beej.us/guide/bgnet/)
* `ncurses` documentation

### Ongoing work
| **Task**                                                                          | **Point person** | **Deliverable**                                           |
|-----------------------------------------------------------------------------------|------------------|-----------------------------------------------------------|
| Single-player game where player can place pixels on a canvas                      | Chris            | Functional single-player game with arrow controls and GUI |
| Build off existing boilerplate code to have multiple clients connect to a server  | Maya             | Multiple clients can connect to the same server           |
| Figure out how to share gamestates between server and client                      | Berwin           | Architecture and/or implementation exists                 |
| Look into getting mouse click coordinates instead of using arrow keys to navigate | Berwin           | N/A, maybe some sample code                               |

### Team Workspaces
* [GitHub repo](https://github.com/olincollege/softsys-rplace)
* [Todoist](https://todoist.com/app/project/2289787951)