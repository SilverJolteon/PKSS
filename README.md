# PKSS

PKSS (*Pokemon Save Selector*) is an app that adds multiple save files to Pokemon games.

## Current Progress

**Currently still in development**

* Checks which games are installed
* Backs up save to location depending on game selected: (sdmc:/PKSS/`<GAME>`/`<SAVE>`/main)
* Prompts keyboard input to name save backup
* Reads from config file of all backed-up saves
* Writes to config file of all backed-up saves
* Displays save info (Trainer name and time played)

### Todo

* Edit UI
* Restore saves
* Launch game automatically
* Copy saves
* Rename saves
* Delete saves
* Reorder saves
* Import from JKSM
* LayeredFS options
* VC Options
* Possibly also NDS Cartridge Options

* Switch to using Citro3d from sf2d
* Switch to using buildtools to compile
* Separate global header into multiple files
* Add error handling

### Credit

Credit goes to Dragos240 for allowing me to use parts of their code from [TownManager](https://github.com/dragos240/TownManager "TownManager Github Repo")