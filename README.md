# PKSS

PKSS (*Pokemon Save Selector*) is an app that essentially allows the user to have mutiple Pokemon game saves.


## Major Update

After a few years of hiatus, I decided to come back to this project and rewrote it in C++.

## Current Progress

**Currently still in development**

* Checks which games are installed
* Backs up and restores saves to location depending on game selected: (sdmc:/PKSS/`<GAME>`/`<SAVE>`/)
* Reads and writes to config file to remember current save in the game
* Automatically launches game with selected save file

### Todo

* Read from/write to cartridge
* Edit UI
* Copy saves
* Rename saves
* Delete saves
* Reorder saves
* Import from JKSM
* LayeredFS options
* VC Options (Already implemented, requires updated UI)
* Possibly also NDS cartridge Options

### Credit

Credit goes to Dragos240 for allowing me to use parts of their code from [TownManager](https://github.com/dragos240/TownManager "TownManager Github Repo")