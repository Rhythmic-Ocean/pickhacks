If you run linux I would recommend just executing the executable file main. You can compile it by yourself, but you should have sdl2, sdl2_image, sdl2_ttf, and sdl_mixer to do it. But if you do have them just type:

`make`

terminal and it should compile everything.

If you use windoes tho, that main.exe files does not work (at least it didn't work on the windows system I tried on), you please watch some youtube tutorial on how to properly set sdl file and install a C compiler and compile it.
<h3>Acknoledgements</h3>

<p>I must thank MLH Group and Missouri S&T University for orginizing this event and giving me an environemt to really lean and explore in the field that I neveer really considered to be of my interest. I must also thank my good friend Amosh Thapa without whom I won't be able to complete this project. I was amazed by his learning speed as despite being a little unfamilair with C, he contributed the entirety of game_screen.c and created the maps in maps.h by typing 0s and 1s by hand.</p>
<h3>About the Game!</h3>
<p>This was created as a project for the PickHacks Hackathon 2025 that took place at Missouri S&T</p>

<p>This game basically has 2 layers and kinda illustrates my learning path of graphics rendering. The first 3 levels basically have the 70s retro vibe while in the last one I tried implementing rendercasting to basically create a "fake" 3d graphics just like the early "3d" games of late 90s (like Doom). No engine was used while creating project as we coded everything in C, with the help of SDL (a library for C/c==) as our guiding hands in this.</p>

<p>AI was used extensively during the creation of this project as the project turned out to be more of a learning oppurtunity than an exercise for me. All I knew before coming to this hackathon was the basics of SDL and the most I had done was create a moveable player sprite and have a text bouncing around the screen. So as I went on to create level 1 I tried creating logic that would help me loop the tiles through out the blank screen but was quickly stopped as even to create a simple 20x20 square outline it took quite a bit of brain power and trying to create a opening in the middel for some king of "gate" as another nightmare in itself. We went to our seniors to ask for help and they recommeneded us to try and use Grok to figure it out and that's bow we learned about tile mapping using 2d array. It was a bit of struggle to write 0s and 1s manually to create maps, but it was a lot better than our initial approach</p>

<p>For raycasting too, we used Grok to get to know how it works and have it write a simple ray casting program to try and understand the logic. From there we tried implementing that progrram to our own game and it worked okish I would say. The walls kinds wraps around itself and although we tried to debug it, we unfortunately didn't have much luxary of time to do that.</p>

<h3><p>Also a thing to note is that raycasting stuffs (2.5d) is only on level 4 because implementing it was quite ambitious for us so we wanted to have our 2d stuffs ready to go before trying this out. And yeah since there's no way to skip levels, you have to walk through the entire map to try it out.</p></h3>
