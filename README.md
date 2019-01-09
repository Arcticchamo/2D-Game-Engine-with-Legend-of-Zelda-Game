# 2D-Engine

This 2D Engine is being designed around a game I am creating inside of it. 
The game is a remake of the original Legend of Zelda but will have new features that will change the gameplay and graphics. 

Currently used within the Engine:
  - SDL - Purely used for the Window.
  - OpenGL - OpenGL is the core of my graphics, currently used for the textures. In the future, this will be expanded upon. 
  - Component Entity System - I am using a CES due to the ease of use when it comes to creating players and enemies. 
  
  - Map Tile Generating Tool - This is a tool I created to help with the formatting of maps. I takes a completed map, seperates it into tiles, then removes any duplicated tiles. This can then be imported into the engine where it will recreate the map but as sectioned chunks. The design around this is due to the overall size of the maps being relatively large in memory. By condensing the maps into a smaller tile map and then re-importing them into the engine where it can be reformed means I can store more maps with less file sizes.
