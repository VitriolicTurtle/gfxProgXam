# gfxProgXam
GFX programming exam, spring 2020. 


## Implementation 
### Controls:
* WASD = Standard movement.
* Mouse = Looking around freely.
* E = Changes position to the duck's. If you hold E and move you will control the duck and follow its movement restrictions.
* Q = Gives you a top down view of the map.

### Proof of concept, implementations made that are incomplete due to time but show competence:
* No sun, but all of its lighting is present in the player, which is therefore the lightsource now, meaning the Phong model is followed.
* You can only take the view of one model, the duck. I just made it so that the last model in the vector is the one gained access to when you hold down E, but all functionality for controlling the model according to its movement restrictions are implemented. 
* **Collision detection is implemented but** the heights on the graphical map doesnt follow the mathematical heights as i couldnt figure out how to make it right in time. BUT IT IS PRESENT, and with a gravity system forcing models down.
* Other things might be specified in comments.

I worked with limited time as 48 hours went to terrain rendring which was useless in the end, before i figured it out.
