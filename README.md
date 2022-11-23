# Source SDK 2013 Community Edition
Source 2013 CE is a clean fork of Valve's [Source SDK 2013 repo](https://github.com/valveSoftware/source-sdk-2013) 
with the goal of fixing up the SDK and to provide a clean bloat-free codebase that works out of the box to make developers' lives easier.

# Info
There are currently two branches, the first one being `master` which will only contain fixes without any extra additions.</br>
The second one is `Experimental` which is the branch we use to add new features and helpful tools for developers.</br>
And a third branch `enhancements` soon to appear, which will include some neat features that we think you will enjoy, 
some made by the community, some backported from other engine branches such as Alien Swarm, and everything in-between.

You can find Source 2013 CE's roadmap by going to our [Trello board](https://trello.com/b/MOxQ2iai/source-sdk-2013-community-edition).

And you can also give us suggestions for fixes and features that you'd like to see in our Discord channel (`#source-SDK-2013-ce`) found in the 
Source Modding Community server, which you can join [here](https://discord.gg/BD6WpY5).

# Building Guide

## Windows
1. Install dependencies Visual Studio 2019 or higher, Multibyte MFC Library, Windows SDK 10.0.22000.0
2. Navigate to `[SDK_ROOT]/[GAME]/src` and run `./createallprojects` or `./creategameprojects`
3. Open Everything.sln or Game.sln and right click on Everything or Game, then select Build Solution

## Linux (Debian)
1. Install dependencies `sudo apt-get install build-essential gcc-multilib g++-multilib`
2. Download Valve's [Steam Runtime repo](https://github.com/ValveSoftware/steam-runtime)
3. Go into the steam-runtime directory and run:
```sh
./setup_chroot.sh --i386
```
4. Run the following commands:
```sh
cd [SDK_ROOT]/[GAME]/src
[SCRIPT]
sudo schroot --chroot steamrt_scout_i386 -- make -f [MAKEFILE].mak
```

# Contributing
We appreciate any form of help so ideally if you want to help this project out the best way would be to make a pull request.

# Ending Notes
Thank you for trying out this project we hope we will help you out with your Source engine troubles!

Made with :heart: by [@Nbc66](https://github.com/Nbc66) & [@GamerDude27](https://github.com/GamerDude27)

Credits for Linux support: Momentum Mod
Credits for 2019 support: Momentum Mod, Brae, and Anthonypython
Credits for CI: TF2Vintage, Deathreus, Dio, Anthonypython
