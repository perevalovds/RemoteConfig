#pragma once

#include "ofMain.h"
#include "ofxKuTextGui.h"
#include "ofxKuTextGuiRemote.h"

//one computer
struct Comp {
	Comp();
	void link_gui(int id, ofxKuTextGui &gui);
	void setup();
	void update(float dt);
	void draw();
	void keyPressed(int key);

	void activate(ofxKuTextGuiRemoteClient &client);
	void deactivate(ofxKuTextGuiRemoteClient &client);

	int id() { return id_; }
	string name() { return name_; }

protected:
	int id_;

	string name_;
	int use_address_;
	vector<string> address_;
	vector<int> port_;
	string addressB_;
	int portB_;

	bool active_;

	int connect_btn_ = 0;	//used only for 1st computer
	int next_btn_ = 0;	//used only for 1st computer
	int prev_btn_ = 0;	//used only for 1st computer

};



