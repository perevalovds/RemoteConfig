#include "ofApp.h"

#include "ofxKuTextGui.h"
#include "ofxKuTextGuiGen.h"
#include "ofxKuTextGuiRemote.h"

#include "gui_generated.h"


//--------------------------------------------------------------
//Show and hide console window
void ShowConsole() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}
//--------------------------------------------------------------
void HideConsole() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

//--------------------------------------------------------------
void ofApp::setup(){

	//comps 
 	n_ = 100;		//number of comps
	comp_.resize(n_);

	gui.set_tab_w(200,10);

	//because of loading gui from "" at the first, 
	//we MUST use _App_title_ and all othervars started with "*"
	PRM setup(gui,""); 
	for (int i=0; i<n_; i++) {
		comp_[i].link_gui(i, gui);	
	}
	gui.loadFromFile("param.ini");

	string title = PRM _App_title_; 
	if (title.empty()) title = "RemoteConfig 1.04";
	ofSetWindowTitle( title );
	cout << "--------------------------------" << endl;
	cout << title << endl;
	cout << "--------------------------------" << endl;
	cout << "Keys: Esc, 1,2, cursor, [,],{,}, Backspace" << endl;
	//ofSetEscapeQuitsApp( false );   


	//Dont's start with Settings page
	if (gui.pageIndex() == 0) {
		gui.setPage(1);
	}

	//screen
	ofSetWindowShape(PRM _Scr_w_, PRM _Scr_h_);
	ofSetFrameRate(PRM _Scr_fps_);   
	if (!PRM _Console_) {
		HideConsole();
	}
	//ofSetWindowTitle(PRM App_title);

	//comps again
	for (int i=0; i<n_; i++) {
		comp_[i].setup();
	}

	flash_ = 0;
	time_ = 0;
	mode_ = 0;
	id_ = -1;

	
}

//--------------------------------------------------------------
void ofApp::exit() {
	save();
	
}

//--------------------------------------------------------------
void ofApp::save() {
	gui.saveToFile("param.ini");
	flash();
}

//--------------------------------------------------------------
void ofApp::flash() {
	flash_ = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
	float time = ofGetElapsedTimef();
	float dt = ofClamp( time - time_, 0.01, 0.1 );
	time_ = time;
	if (flash_>0) flash_ -= dt/0.5;

	for (int i=0; i<n_; i++) {
		comp_[i].update(dt);
	}

	gui.update();
	if (mode_ == MODE_SETUP) {
		//Buttons
		if (*gui.findVarButton("Connect")) {
			*gui.findVarButton("Connect") = 0;
			activate();
		}
		if (*gui.findVarButton("Next")) {
			*gui.findVarButton("Next") = 0;
			gui.gotoNextPage();
		}
		if (*gui.findVarButton("Previous")) {
			*gui.findVarButton("Previous") = 0;
			gui.gotoPrevPage();
		}
	}
	//Constrain number of computers
	if (gui.pageIndex() > PRM _Max_n_) {
		gui.setPage(PRM _Max_n_);
	}

	if (mode_ == MODE_COMP) {
		Comp &comp = comp_[id_];
		comp.update(dt);
		client_.update();
	}


}

//--------------------------------------------------------------
void ofApp::draw(){
	if (mode_ == MODE_SETUP) {
		if (gui.pageIndex() == 0) {
			//Settings
			ofBackground(64, 64, 80);
		}
		else {
			ofBackground(80, 80, 64);
		}

	    gui.draw(20, 30);
		//client.draw(20, 150);

		if (flash_>0) {
			ofSetColor(255, 255*flash_);
			ofFill();
			ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
		}
	}
	if (mode_ == MODE_COMP) {
		ofBackground(64);
		Comp &comp = comp_[id_];
		ofDrawBitmapStringHighlight("Connecting to '"// + ofToString(comp.id()+1,2,'0') + " " 
			+ comp.name()
			+ "'     Press Backspace to return to menu", 20, 30);
		client_.draw(20,65);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//Backspace - go to edit/back to comp list
	if (mode_ == MODE_SETUP) {
		if (key == OF_KEY_BACKSPACE) {
			activate();
			return;
		}

		if (gui.keyPressed(key)) return;

		if (key == 's') save();
	
		if (key == 'G') {   //Generate .H and .CPP files for parameters
		    ofxKuTextGuiGen::generateCPP("gui/gui-script.ini",
			                             "../../src/", "gui_generated",
				                         "Parameters", "params", "PRM");
			flash();
		}
		return;
	}
	if (mode_ ==  MODE_COMP) {
		if (key == OF_KEY_BACKSPACE) {
			deactivate();
			return;
		}
		client_.keyPressed(key);
		return;
	}
}

//--------------------------------------------------------------
void ofApp::activate() {
	int id = gui.pageIndex() - 1;
	if (id >= 0 && id < n_) {
		activate(id);
	}
}

//--------------------------------------------------------------
void ofApp::activate(int id) {
	deactivate();
	mode_ = MODE_COMP;
	id_ = id;
	comp_[id_].activate(client_);
	client_.askGuiRequest();

}

//--------------------------------------------------------------
void ofApp::deactivate() {
	mode_ = MODE_SETUP;
	if (id_>=0) {
		comp_[id_].deactivate(client_);
		id_ = -1;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//client.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (mode_ == MODE_SETUP) {
		gui.mouseDragged(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (mode_ == MODE_SETUP) {
		gui.mousePressed(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (mode_ == MODE_SETUP) {
		gui.mouseReleased(x, y, button);
	}

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
