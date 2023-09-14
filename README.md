# time_dork
This is a Test delivery for my appliance into the UPCSchool's AAA videogame Programming masters degree.

author: Jordi Alonso Llovet<br />
email: jordi.alonso.llovet@gmail.com<br />
github: https://github.com/JordiAlonsoLlovet/Zork<br />
MIT license: https://github.com/JordiAlonsoLlovet/Zork/blob/main/LICENSE<br />

This is a game inspired by the 1977's Zork as well as classic point and click games.
I've removed any RPG or combat elements in favour of puzzle like mechanics, so it is not possible
to die or lose.<br />
The game has a mechanic introduced in the first room that lets you travel between any room and
a version of that same room in the past. Droping or removing items in the past may change
some areas in the present.

# Dificulties
I must admit that I got overconfident  with this project. It has been a long time since I worked with c++, and I ended up rushing the code a bit. It is still completely functional and as far as I know there are no bugs, but poor planning of the class structure and how to keep track of every entity in the game has lead the game code to be a bit messy, and with too much code duplication.<br />
Specifically, searching for the entity that the player is interacting with became extremely time consuming and I ended up writing the same for loop structure way too many times for way too many different functions that either search for an item in the inventory, in the room, in both, search for available paths...

# Time travel
The time travel mechanic works by having each room be an object (Room4d) that holdes two or three different rooms; one for the past, one for the present and an optional thir one for a changed version of the present. And I managed to make the code for adding rooms, paths, items, and even the specific conditions that make a room "change" as simple and lightweight as possible; which means it would be trivially easy to expand the game, or make entirely new maps in a pretty flexible manner.

# WALKTHROUGH
0 - You are in an area with no exits, just a box.<br />
1 - Open the box [open box]<br />
2 - Take the clock [take clock]<br />
3 - Go to the past [clock, watch, c]<br />
4 - Now you can go north [north]<br />
5 - Go back to the present [clock, watch, c]<br />
6 - Inspect the tree [look tree]<br />
7 - Take the apple <br />
8 - Open (or eat) the apple<br />
9 - Take the seed<br />
10 - Go west<br />
11 - Go to the past<br />
12 - Take the trash (either take trash, take garbage, take rubbish or take bag will work)<br />
13 - Beck to the present.<br />
14 - Take the sword.<br />
15 - Go East<br />
16 - Take the torch<br />
17 - Go East<br />
18 - Burn the spiders [use torch on spiders, use torch on cowebs, burn spiders with torch, attack spiders with fire...]<br />
19 - Go North twice.<br />
20 - Kill the dragon with the sword [attack dragon with sword...]<br />
21 - Go North<br />
22 - Go to the past<br />
23 - Put seed in the soil [put seed in soil]<br />
24 - Back to the present, and YOU WON!<br />

