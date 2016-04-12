# Computer Graphics Coursework
This was a piece of software written for a computer graphics module I took while attending university.

![Screenshot](https://github.com/Mattiemus/Graphics/blob/master/screenshot.png?raw=true)

# Lighting
As 3D rendering is essentially just a simulation of lighting bouncing around a scene, great care was taken with the lighting engine. The Phong lighting model was implemented in HLSL, which defines how light should diffuse around an object, and how to compute specular highlights.

![Screenshot](https://github.com/Mattiemus/Graphics/blob/master/screenshot2.png?raw=true) ![Screenshot](https://github.com/Mattiemus/Graphics/blob/master/screenshot3.png?raw=true)

# Texturing and Shaders
Textures were used to define the individual components in the lighting simulation. The shaders take in maps for the diffuse colour, the surface normal, and the specular highlights. These maps are then combined into a material. A material is a single shader, with its input bindings (i.e. textures, camera matrices, etc.). These maps are loaded using SDL, by reading the texture file as a surface, then loading the byte array into OpenGL.

![Screenshot](https://github.com/Mattiemus/Graphics/blob/master/screenshot4.png?raw=true)

![Screenshot](https://github.com/Mattiemus/Graphics/blob/master/screenshot5.png?raw=true)

# Animation
The scene has two key animated parts, both the grass and the planetary model. You can see the grass, which sways in the wind, by transforming the tips of the grass according to sin(elapsedTime). The second animated component is the planetary model, shown above, which makes use of hierarchical modelling to rotate the planets both around the centre column, and the moons around there parent planet. This is done by simply rotating the object around there origin axis (the very end of their arm).

![Screenshot](https://github.com/Mattiemus/Graphics/blob/master/screenshot6.png?raw=true) ![Screenshot](https://github.com/Mattiemus/Graphics/blob/master/screenshot7.png?raw=true)
