# RemoteConfig

RemoteConfig is an application for remote control programs used ofxKuTextGui interface via OSC.

## Features
* Control up to 100 programs using keyboard.
* Set up computer names.
* Made in openFrameworks (and is based on KuRemote free app by perevalovds).

## Keys
* Esc - close app
* 1, 2, Shift+1, Shift+2 - choose the page (Settings, Comp01, ..., Comp16)
* Cursor - choose value to edit (name, address, port)
* [, ], Shift+[, Shift+] - edit value
* BackSpace - connect to the remove app, and disconnect back. After connection, KuRemote sends key presses to remote app,
and requests GUI description, and draws it on the screen. 

Remote app, such as KuRemoteTst, should contain object ofxKuTextGuiRemote class,
which will respond to KuRemote app requests.

## Build 
To build the projects KuRemote and KuRemoteTst:
1 install openFrameworks, 
2 install our ofxKuTextGui addon,
3 Create a new project with Project Generator (KuRemote / KuRemoteTst), which inclused ofxOsc and ofxKuTextGui addins
4 Press Generate.
5 Enjoy!


