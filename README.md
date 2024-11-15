# GTRUNNER
Gtk Tray Runner

<img src="https://raw.githubusercontent.com/ItzSelenux/ItzSelenux.github.io/main/res/projects/gtrunner.svg" alt="GTRunner Logo" width="111px" />

**GTRUNNER** is a simple tool for creating tray indicators that can run shell commands.

## Features

- [x] Create Tray icons with menus
- [x] Edit tray entries with a GUI
- [x] Multiple entries at the same time

## Installation

- Clone
	- ``` 
		git clone https://codeberg.org/ItsZariep/GTRunner
		```
- Make
	- ```sh
		cd GTRunner
		make
		```


## Usage

You can create GTRunner entries with the integrated GUI (`use gtrunner --gui` in indicator menu) or by editing` $HOME/.config/gtrunner` using the following Syntax:


```ini

[Trayname 1]
icon=icon-here
elements=Element 1, Element 2, Element 3
commands=command 1, command 2, command 3

[Example]
icon=start-here
elements=GIMP, Inkscape, Krita
commands=gimp, inkscape, krita

```


## Config values

| Item       | Description                                           | Example                                   |
|------------|-------------------------------------------------------|-------------------------------------------|
| `icon`     | Set a icon (can be from icon theme or absolute path)  | `icon=start-here`                         |
| `elements` | Set elements                                          | `elements=Task Manager, text editor `     |
| `commands` | Set commands (according to the order of the elements) | `commands=st -e htop, xed --new-document` |