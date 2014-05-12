#Island Generator
A hobby project. I want to create a somewhat realistic terrain generator from above. It currently fills the middle with random numbers and expands it based on the chosen iterations. Low sizes(approx 4) and high iterations create singular circular islands, while higher sizes (approx. 8) create more squarish and split up islands.

![Island bmp](https://raw.githubusercontent.com/mholmPurdue/Island-Generator/master/island.png)

##todo
* Create a map-styled output using edge detection at a certain threshold
* I plan on rewriting part of the randomization code to prevent things from getting too squarish. Performance is fast enough that the extra computation shouldn't be an issue
* Different color scheme
* Improved color flexibility (currently just 16, can be raised easily but I haven't considered the effects on randomization with it.)
* ~~Introduce randomization on expansion to counteract the obvious lines being generated by the algorithm~~
* ~~Switch from text output to .bmp output~~
