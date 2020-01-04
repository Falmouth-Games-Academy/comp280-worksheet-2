# comp280 worksheets

###### Table of contents

1. [Networking](#1-Networking)  
2. [AI](#2-AI)  
3. [Graphics](#3-Graphics)  
4. [Interfaces & Interaction](#4-Interfaces--Interaction)   
5. [Software, tools and assets used](#5-Software-tools-and-assets-used)
6. [Git Repo's](#6-git-repos)


---

## 1. Networking
Pacman-ish uses a python http server to store and load leader board and game 
balance data from a sqlite database. [see repo](https://github.com/Ashley-Sands/Comp-280-PythonServer)
(the database can be viewed using the [AMSqlite tool](https://github.com/Ashley-Sands/SQLightExplorer))  
###### The Code
Sending and requesting data to and from the sever is handled by   
```
Source\comp280_worksheet_2\Pacman_gameInstance.h
Source\comp280_worksheet_2\Pacman_gameInstance.cpp
Source\comp280_worksheet_2\Http_Request.h
Source\comp280_worksheet_2\Http_Request.cpp
```
The server sends and receives data in json format which is then converted to/from structs
```
Source\comp280_worksheet_2\jsonContatiners.h
```
(among the structs is a class that is used to get the data into the leader board tree view)

The ```BP_leaderboard``` blueprint widget triggers the leader board request  
and ```GM_MainMenus``` blueprint game mode loads the games settings in.  
(Both located in ```\Content\MainMenuUI\```)

## 2. AI
Iv attempted to recreated original PacMan AI according to [GameInternals](https://gameinternals.com/understanding-pac-man-ghost-behavior)

All AI Behaviour Trees and task can be found in
```
\Content\AiContr\
```
All ghost use the same blackboard ```GhostBB```  
There is a controller and Behaviour tree for each ghost
which all share a group of task located in the ```Task``` folder

## 3. Graphics
New Materials (By Game Mode)
#### Classic Mode
- Glitchy ghost material for when a power pill has been eaten  
```\Content\materials\Ghost```

#### FPS Mode
- Glitchy transparent walls when a power pill has been eaten  
```\Content\materials\m_ghostly```
- Scan line post processing (also used on main menu)  
```\Content\PostProcessing\VedioScan```

#### Both Modes
- Colour lerp pill  
```\Content\materials\m_pickup1```
- Glitchy Power Pills  
```\Content\materials\Pill_Trip```

## 4. Interfaces & Interaction
The Menus and HUD have been implemented and enhance based on the initial 
heuristic evaluation.  
(There is no health bar! since its not really applicable to the game)  
Furthermore there has been a 'Game Over' screen added where the user can 
input there name with error prevention implemented to prevent the user from
submitting a score without entering a name.
#### Menus
- Main menu  
```\Content\MainMenuUI\BP_MainMenu_UI```
- Leader board  
```\Content\MainMenuUI\BP_leaderboard```
- Pause menu  
```\Content\MainMenuUI\BP_PauseMenu_UI```
- Controls  
```\Content\MainMenuUI\BP_Controls_UI```
- Game over screen  
```\Content\MainMenuUI\BP_GameOver_UI```

#### Classic Mode HUD
- HUD (ALL)  
```\Content\ThirdPersonBP\Blueprints\HudWidget```
#### FPS Mode HUD
- Radar HUD  
```\Content\FirstPersonBP\Map\ui_miniMap```
- Ammo HUD  
```\Content\FirstPersonBP\Blueprints\ui_ammo```
- cam overlay  
```\Content\FirstPersonBP\Blueprints\ui_can_overlay```
---

## 5. Software, tools and assets used

#### Web Server & Client
To run the web Sever and Client from source use python 3.7 with PyQt5 (v5.13.2) installed  
The server and client have been built using PyInstall 3.5

#### Pacman-ish (Game)
Requires Unreal Engine version 4.22.3

#### UI/UX Prototype
Adobe XD

#### Used Assets from the web
["Ghost" 3D model by Luca Perencin](https://poly.google.com/view/6tcLAzFt-A2), licensed under CC-BY.  
["shotgun-reload" sound fx by RA The Sun God](http://soundbible.com/1961-Shotgun-Reload-Spas-12.html) licensed under CC-BY.  
["Empty Gun Shot" sound FX by KlawyKogut](https://freesound.org/people/KlawyKogut/sounds/154934/), licensed under CC-Zero  
["Designed Element, Ghostly Breath, Pulsating, Inhale and Exhale, Soul Spirit or Spectre"](https://www.zapsplat.com/music/designed-element-ghostly-breath-pulsating-inhale-and-exhale-soul-spirit-or-spectre/), zap splat standard license  

This project uses sound fx from [ZapSplat](https://www.zapsplat.com)

## 6. Git Repos
Pacman-ish game:    [https://github.com/Ashley-Sands/comp280-worksheet-2](https://github.com/Ashley-Sands/comp280-worksheet-2)  
Python, Web Sever:  [https://github.com/Ashley-Sands/Comp-280-PythonServer](https://github.com/Ashley-Sands/Comp-280-PythonServer)  
SQLite Web Client:  [https://github.com/Ashley-Sands/SQLightExplorer](https://github.com/Ashley-Sands/SQLightExplorer)  
