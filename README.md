#Island Generator
A hobby project. I want to create a somewhat realistic terrain generator from above. It currently fills the middle with random numbers and expands it based on the chosen iterations. Low sizes(approx 4) and high iterations create singular circular islands, while higher sizes (approx. 8) create more squarish and split up islands.

-name="X.bmp" -_Sets the filename for the bmp file output_  

-size="#"     -_Sets the initial grid size for the map_   

-i="#"        -_Sets the number of iterations (multiplies size by 2^i)_   

-cart         -_Changes color scheme to a more mappish style_   

-edges        -_Removes the 0's from the edge of the map, allowing it to emulate a map section instead of an island_   


![Island bmp](https://raw.githubusercontent.com/mholmPurdue/Island-Generator/master/island.png)

##todo
* Third dimension? I'd have to port it all to javascript, but thats really the only way I can see this going. Might just be done with it
* ~~I plan on rewriting part of the randomization code to prevent things from getting too squarish. Performance is fast enough that the extra computation shouldn't be an issue~~
* ~~Create a map-styled output using edge detection at a certain threshold~~
* ~~I plan on rewriting part of the randomization code to prevent things from getting too squarish. Performance is fast enough that the extra computation shouldn't be an issue~~
* ~~Different color scheme~~
* ~~Improved color flexibility (currently just 16, can be raised easily but I haven't considered the effects on randomization with it.)~~
* ~~Introduce randomization on expansion to counteract the obvious lines being generated by the algorithm~~
* ~~Switch from text output to .bmp output~~
