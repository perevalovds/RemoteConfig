#pragma once
//Auto-generated GUI file for ofxKuTextGui, 2019-09-09-02-33-36-205

#include "ofMain.h"
#include "ofxKuTextGui.h"

struct Parameters {
	string App_title;
	string _App_title_;
	int Max_n;
	int _Max_n_;
	int Next;
	int Scr_w;
	int _Scr_w_;
	int Scr_h;
	int _Scr_h_;
	int Scr_fps;
	int _Scr_fps_;
	int Console;
	int _Console_;
	int OSC_in_port;
    Parameters();
    void setup(ofxKuTextGui &gui, string fileName);
    void save();
    string fileName_;
    ofxKuTextGui *gui_;
};

extern Parameters params;
#define PRM params.
