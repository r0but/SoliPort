# SoliPort
This is an attempt to modify my game, Soliton, to use the SFML graphics library instead of a command terminal. I am working on a complete rewrite of it as well, but for now, this is a quick and dirty solution to have something cool to show while I create a cleaner codebase.

For the original game, please visit github.com/r0but/Soliton.

My current environment is OS-X 10.10 with XCode 6.1.1. It shouldn't be too hard to build it for other platforms if you follow the tutorials at: http://www.sfml-dev.org/tutorials/2.2/

The main snag in building for other platforms will likely be the resourcePath() function, as it exists specifically to find program resources such as sprites within its .app package. This is specific to OS-X. If building for other platforms, you should remove all calls to that function and replace them with proper file paths for your OS.
