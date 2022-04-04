# Magma Boy and Hydro Girl 2: Electric Boogaloo
## Chris Allum, Maya Sivanandan, Berwin Lan

### Reflection on Project 1
* **Berwin and Maya** (worked together last time)
    * having a standing weekly meeting time to pair program and work on tricker bugs
    * standing meeting also helpful for keeping work level consistent and avoiding procrastination
    * using a Messenger group chat to communicate asynchronously and report progress on deliverables
    * assigning action items and responsible individuals at the end of every weekly meeting
* **Chris**
	* Experience was mostly good! I learned a lot, but if I had to change something, I would have liked to have had some more organization in workflow. For this project, inherently by working with others, I will have to force myself to be organized and dependable in terms of getting things done in a timely manner.
	* I enjoyed writing C as a language

### Project Goals
* lower bound
    * two-player platformer game over a network
    * WASD or arrow key controls with basic physics
    * built entirely in C (no Python embedding)
* stretch goals
	* a two-client, one-server model (as opposed to a client and a server)
    * a really nice GUI

### Learning Goals
* working with threading and semaphores
* more advanced networking than both our Project 1s
* an interactive and engaging game

### Starting Resources

* Library to help with making the platformer (~pygame)
* [Raylib looks like it has a lot of similar features as pygame](https://www.raylib.com/index.html)
* [libsdl - Simple DirectMedia Layer](https://www.libsdl.org/)
* [MagmaBoy and HydroGirl Python Implementation](https://github.com/ctallum/MagmaBoy-and-HydroGirl-Game) 

* Might need resources on running processes on client/host simultaneously - last time we used resources from Head First C, as well as some online resources (see [Project 1: TicTacToad](https://github.com/emmamack/TicTacToad/blob/main/reports/report.md#resources))

### First steps and action items

| **Task**                                                                                                                    | **Point person** | **Deliverable**                                                            |
|-----------------------------------------------------------------------------------------------------------------------------|------------------|-----------------------------------------------------------------------------------|
| Install `raylib` and run sample code on each of our devices                                                                 | Everyone         | We are able to run files that depend on `raylib`                                  |
| Boilerplate code/formatting                                                                                                 | Chris            | Code architecture is outlined with file placeholders                              |
| Look into how graphics work in `raylib`                                                                                     | Maya             | Can find analogous functions to what was used in the Python/pygame implementation |
| Look over the [SoftDes project](https://github.com/ctallum/MagmaBoy-and-HydroGirl-Game) to understand Python implementation | Berwin           | Understand code architecture and pygame functions used                            |
| Investigate physics and collisions in `raylib`                                                                              | Berwin           | Can find analogous functions to what was used in the Python/pygame implementation |