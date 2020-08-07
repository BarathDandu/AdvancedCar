# RayCast Car
## C++ Project made from scratch using the Pawn Class in Unreal Engine 4.

This project uses the RayCast and many other Features that unreal provides to make a car.

- The Car is a Single mesh, it is not a skeletal mesh and it doesnt use any additional tire data and other stuff that unreal uses by default.
- The entire car in made in one C++ class and every parameter can be changed to make different models or change the driving dynamics of the car.
- The Car Uses LineTraceByChannel combined with AddForceAtLocation to find the suspension strength.
- It uses velocity of each tire to find the friction force that should be applied.
- Uses 2 curves for steering inputs and the engine functionality. 
- 3 forces, one in each axis are calculated using multiple functions and are put into a single FVector and are applied using AddForceAtLocation.
- The wheels dont have any collision and are there just for making it look like a car, the car will behave the same even without them.
- The car can also be controlled in the air to adjust the landing angle, it can also be flipped when its tipped over, so that you don't have to exit the game to drive again.
- Engine sound and tire rolling sound are integrated using FMOD these are the only functions that use bluprints in the entire car.



[Download link for the playable Demo](https://www.mediafire.com/file/78sxf5qe13k6gyy/RayCast+Car.zip/file)

[Youtube link for video Demo](https://www.youtube.com/watch?v=L8TCZViTOac)

![](Screenshot%20(98).png)
![](Screenshot%20(108).png)
![](Screenshot%20(105).png)
