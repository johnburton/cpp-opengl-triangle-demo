# OpenGL triangle demo

A simple demonstration of a rotating triangle using opengl.

- Set up a window using glfw.
- Create a vertex buffer containing the vertex data.
- Create a shader from the shader code embedded in the program.
- Pass in model, view and projection matrices to the shader.
- Rotate the model 1 degree per frame.

This is tested and works on Linux x86-64 (Mint Linux)
- It requires the following libraries to be installed :-
  - glfw
  - glew
  - glm