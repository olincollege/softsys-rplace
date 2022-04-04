# Magma Boy and Hydro Girl 2: Electric Boogaloo
## Chris Allum, Maya Sivanandan, Berwin Lan

### 1) Briefly, how was your experience with the last project? In light of that experience, what, if anything, will you do differently in this project?
* **Berwin and Maya** (worked together last time)
* having a standing weekly meeting time to pair program and work on tricker bugs
* standing meeting also helpful for keeping work level consistent and avoiding procrastination
* using a Messenger group chat to communicate asynchronously and report progress on deliverables
* assigning action items and responsible individuals at the end of every weekly meeting
* **Chris**
	* Experience was mostly good! I learned a lot, but if I had to change something, I would have liked to have had some more organization in workflow. For this project, inherently by working with others, I will have to force myself to be organized and dependable in terms of getting things done in a timely manner.
	* I enjoyed writing C as a language

### 2) What is the goal of your project; for example, what do you plan to make, and what should it do?  Identify a lower bound you are confident you can achieve and a stretch goal that is more ambitious.
* lower bound
* two-player platformer game over a network
* WASD or arrow key controls with basic physics
* built entirely in C (no Python embedding)
* stretch goals
	* a two-client, one-server model (as opposed to a client and a server)
* a really nice GUI

### 3) What are your learning goals; that is, what do you intend to achieve by working on this project?
* working with threading and semaphores
* more advanced networking than both our Project 1s
* an interactive and engaging game

### 4) What do you need to get started?  Have you found the resources you need, do you have a plan to find them, or do you need help?

* Library to help with making the platformer (~pygame)
* [Raylib looks like it has a lot of similar features as pygame](https://www.raylib.com/index.html)
* [libsdl - Simple DirectMedia Layer](https://www.libsdl.org/)
* [MagmaBoy and HydroGirl Python Implementation](https://github.com/ctallum/MagmaBoy-and-HydroGirl-Game) 

* Might need resources on running processes on client/host simultaneously - last time we used resources from Head First C, as well as some online resources (see [Project 1: TicTacToad](https://github.com/emmamack/TicTacToad/blob/main/reports/report.md#resources))

### 5) What are your first steps?  Describe at least three concrete tasks that you can do immediately, and identify which member of the team will do them.  For each one, what is the | **Task**                                                                                                                    | **Point person** | **Definition of done**                                                            |
|-----------------------------------------------------------------------------------------------------------------------------|------------------|-----------------------------------------------------------------------------------|
| Install `raylib` and run sample code on each of our devices                                                                 | Everyone         | We are able to run files that depend on `raylib`                                  |
| Boilerplate code/formatting                                                                                                 | Chris            | Code architecture is outlined with file placeholders                              |
| Look into how graphics work in `raylib`                                                                                     | Maya             | Can find analogous functions to what was used in the Python/pygame implementation |
| Look over the [SoftDes project](https://github.com/ctallum/MagmaBoy-and-HydroGirl-Game) to understand Python implementation | Berwin           | Understand code architecture and pygame functions used                            |
| Investigate physics and collisions in `raylib`                                                                              | Berwin           | Can find analogous functions to what was used in the Python/pygame implementation |