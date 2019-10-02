#include "gui_generated.h"
//Auto-generated GUI file for ofxKuTextGui, 2019-09-09-02-33-36-209

Parameters params;
//--------------------------------------------------------------
Parameters::Parameters() {
	_App_title_="RemoteConfig";
	_Max_n_=10;
	Next=0;
	_Scr_w_=1024;
	_Scr_h_=768;
	_Scr_fps_=30;
	_Console_=0;
	OSC_in_port=12350;
}

//--------------------------------------------------------------
void Parameters::setup(ofxKuTextGui &gui, string fileName) {
	gui.addPage("Settings");
	gui.addDummy("App title:");
	gui.addString("*App_title",_App_title_,"RemoteConfig");
	gui.addDummy("Max computers:");
	gui.addInt("*Max_n",_Max_n_,10,1,100,1,10);
	gui.addDummy("");
	gui.addButton("Next",Next);
	gui.addTab();
	gui.addTab();
	gui.addDummy("Screen:");
	gui.addInt("*Scr_w",_Scr_w_,1024,1,10000,1,50);
	gui.addInt("*Scr_h",_Scr_h_,768,1,10000,1,50);
	gui.addInt("*Scr_fps",_Scr_fps_,30,1,100,1,10);
	gui.addStringList("*Console",_Console_,0,2,"OFF","ON");
	gui.addDummy("OSC:");
	gui.addInt("OSC_in_port",OSC_in_port,12350,1,65535,1,50);
	gui.addTab();
	gui.set_var_color("*App_title", ofColor(140,255,140));
	gui.set_var_color("*Max_n", ofColor(140,255,140));
	gui.set_var_color("OSC_in_port", ofColor(255,255,100));
	fileName_ = fileName;
	gui_ = &gui;
	gui.loadFromFile(fileName);
	App_title = _App_title_;
	Max_n = _Max_n_;
	Scr_w = _Scr_w_;
	Scr_h = _Scr_h_;
	Scr_fps = _Scr_fps_;
	Console = _Console_;
}

//--------------------------------------------------------------
void Parameters::save() {
	gui_->saveToFile(fileName_);
}

//--------------------------------------------------------------

