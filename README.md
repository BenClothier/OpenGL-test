# OpenGL Project Template
A project with the GLAD and GLFW libraries already set up.

Get started with OpenGL by following this guide:
[Getting started with OpenGL](https://learnopengl.com/Getting-started/OpenGL)

## Building & Running
Some handy batch files have been provided which will handle the whole build process.

This includes...

`clean.bat`
`rescan.bat`
`build.bat`
`run.bat`

And finally, to run all of the above files...

`all.bat`

## Accessing Resources
Any files like shaders and images that your program will need to access can be stored in the `resources` folder.
Since the program will execute at the root directory (and not where the executable is located), you can use relative file paths like so...

`"resources/my-resource.png"`
`"resources/shaders/my-shader.vs"`
