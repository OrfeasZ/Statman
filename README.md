![Logo](http://i.imgur.com/lSCUfwF.png)

### Introduction

Statman is a configuration-free and easy-to-use live statistics tracking program for games.

It has been built from the ground up to allow for easy tracking integration of different games and engines, while abstracting the underlying complexity from the end-user. Additionally, Statman features two themes (a light one and a dark one), switcheable by double-clicking the Statman logo, and update-checking features to ensure that your version is always up-to-date.

Statman is currently in early stages of development, so there could still be issues and bugs. If you encounter any issues please feel free to report them on the [Issue Tracker](https://github.com/OrfeasZ/Statman/issues).

### Supported Games & Features

 - Hitman: Blood Money (HM3)
   - Live tracking of the following statistics:
     - Witnesses
     - Bodies Found
     - Covers Blown
     - Caught on Camera
     - Frisk Failed
     - Items Left on Level
     - Enemies Killed
     - Enemies Wounded
     - Policemen Killed
     - Policemen Wounded
     - Innocents Killed
     - Innocents Wounded
   - Live tracking of in-game level time
   - Live tracking of the current level and state
   - Live tracking of the current level rating
   - Live tracking of the current difficulty setting
   - Ability to enable and disable cheats
   - Ability to enable unlimited saving/loading for all difficulties
   - Hitman 2016 Mode (Experimental)
   - In-game tracker overlay

### Hitman Blood Money: 2016 Mode

This is an experimental mode that adds support for custom starting locations with alternative disguises. You can find more info about how it works and how to configure it [here](/HM3_2016.md).

### Screenshots

![Screenshots](http://i.imgur.com/rOowYzX.png)

### Download

 - [Version 1.4.0.0](https://github.com/OrfeasZ/Statman/releases/download/v1.4.0.0/Statman_1.4.0.0.zip) (Latest)
 - [Version 1.3.3.0](https://github.com/OrfeasZ/Statman/releases/download/v1.3.3.0/Statman_1.3.3.0.zip)
 - [Version 1.3.2.0](https://github.com/OrfeasZ/Statman/releases/download/v1.3.2.0/Statman_1.3.2.0.zip)
 - [Version 1.3.1.0](https://github.com/OrfeasZ/Statman/releases/download/v1.3.1.0/Statman_1.3.1.0.zip)
 - [Version 1.3.0.0](https://github.com/OrfeasZ/Statman/releases/download/v1.3.0.0/Statman_1.3.0.0.zip)
 - [Version 1.2.0.0](https://github.com/OrfeasZ/Statman/releases/download/v1.2.0.0/Statman_1.2.0.0.zip)
 - [Version 1.1.0.0](https://github.com/OrfeasZ/Statman/releases/download/v1.1.0.0/Statman_1.1.0.0.zip)
 - [Version 1.0.0.0](https://github.com/OrfeasZ/Statman/releases/download/v1.0.0.0/Statman_1.0.0.0.zip)


### Usage

In order to use Statman you simply need to extract the binaries from the downloaded archive (or compile it yourself), and run **Statman.exe**. It is recommended to start Statman before starting the game in order to have full tracking capabilities from the beginning.

Game-specific features can be accessed by right-clicking on the statman logo while the game is running.

### Building

Clone the git repo and ensure all submodules are checked out by running:

```sh
git submodule update --init --recursive
```

Make sure that the [DirectX SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812) is installed.

Then open `Statman.sln` in Visual Studio 2022, select the `x86` platform target for using Statman with Hitman Blood Money, or the `x64` platform target for using it with Hitman 2016+, and press `|> Start`.