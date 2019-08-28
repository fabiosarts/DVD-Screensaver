# DVD Screensaver

A old school DVD screensaver remake for Microsoft Windows
It includes Visual Studio 6 and Visual studio 2017 project files

## Other compilers
For other compilers you need to add *scrnsave.lib* and *comctl32.lib* in required libraries (probably the last one isn't needed for every compiler) and set as Windows Application (not console) as Windows specific entry point is on *scrnsave.lib*

## Executable downloads
You can get the precompiled files for any [Windows 95-98](https://github.com/fabiosarts/DVD-Screensaver/releases/download/v1.1/DVD-Screensaver-1.1-VS6.zip) and any [Modern Windows platform](https://github.com/fabiosarts/DVD-Screensaver/releases/download/v1.1/DVD-Screensaver-1.1-VS2017.zip).

## Changelog
* V1.1
  * Added multiple monitor support (only VS2017 version)
  * Refractorized code to be more modular
