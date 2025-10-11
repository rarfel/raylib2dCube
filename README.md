# Making a 3d engine in a 2d enviroment

This is a remake of another project, but now in c++ and raylib.  

The techiniques to achive "3d" graphics will be the same: `Weak Projection`

## The previous Project

The <a href="https://github.com/rarfel/3d-cube">"3d-cube"</a> was made with javascript and html canvas, in only a few hours, I came back after to clean some things here and there but noticed that would be pretty hard to escalete it further because of the messy code.  

Now I want to do it again but with patience, and a clearer goal: make a easy-to-use 3d visualizer.

I had a lot of expirence with javascript and html canvas when I did the previous version, but in the making of this project I have none in raylib, I was thinking of making this project in SDL3, but decide against it because I found raylib easier to setup.

## Weak Projection 

The basic premise is to use 2d coordinates and matrix multiplication to achive 3d graphics, the core formula is `Projected = x or y / z`, where:  

`x` and `y` are the cartesian points of a plane.  
`Projected` is the calculated point of `x` or `y` afeter the <i>matrix multiplication</i>.  
`z` is the "distance from the camera", or how "far"  the object is from the viewer.

More informations on <a href="https://en.wikipedia.org/wiki/3D_projection#Weak_perspective_projection">Weak Perspective</a> and <a href="https://en.wikipedia.org/wiki/Transformation_matrix#Perspective_projection">Matrix Multiplication<a/>.  