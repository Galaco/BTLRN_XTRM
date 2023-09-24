# BTLRN_XTRM

A small platformer game written as a university assignment circa. 2013.

## Features

* Multiple levels, including support for custom levels
* Basica graphical configs
* Highscores table
* Some enemies and powerups


## Building

This project is compilable for Windows and Mac OS. Linux support is untested.

#### Windows

Visual Studio 2013 project is available for Windows. Probably requires no setup, just open the .sln and away you go.

#### Mac OS

Recommend first installing SFML 2.6 via Brew, as that will place the libs in the relevant place:

```
brew install sfml
```

A VSCode project & build configuration is available; so open the project in VSCode and compile by running the included task.
If using a different minor version of SFML you may need to update `.vscode/tasks.json` (SMFL 2.5 and 2.6 are known to both compile successfully).