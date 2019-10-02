#include "Comp.h"
#include "gui_generated.h"

//--------------------------------------------------------------
Comp::Comp() {
	active_ = false;
}

//--------------------------------------------------------------
void Comp::link_gui(int id, ofxKuTextGui &gui) {
	id_ = id;
	int n = 2;
	address_.resize(n);
	port_.resize(n);


	string name = ofToString(id+1,2,'0');
	string prefix = name + "_";
	string suffix = "_" + name;
	gui.addPage(name);

	gui.addString(name, name_, "Computer" + name);

	gui.addDummy();
	if (id == 0) {
		gui.addButton("Connect", connect_btn_);
		gui.addDummy();
		gui.addButton("Previous", prev_btn_);
		gui.addVar("Next");
	}
	else {
		gui.addVar("Connect");
		gui.addDummy();
		gui.addVar("Previous");
		gui.addVar("Next");
	}

	gui.addTab(2);
	gui.addStringList("Use_addr" + suffix, use_address_, 0, 2, "Variant_A", "Variant_B");

	gui.addDummy("Variant_A:");
	gui.addString("AddrA" + suffix, address_[0], "localhost");
	gui.addInt("PortA" + suffix, port_[0], 12300, 1, 65535, 1, 50);

	gui.addDummy("Variant_B:");
	gui.addString("AddrB" + suffix, address_[1], "localhost");
	gui.addInt("PortB" + suffix, port_[1], 12300, 1, 65535, 1, 50);


	//Colors
	ofColor addr_color1(100, 255, 255);
	ofColor addr_color2(255, 100, 255);

	gui.set_var_color(name, ofColor(100, 255, 100));
	gui.set_var_color("Use_addr", ofColor(255));

	gui.set_var_color("AddrA" + suffix, addr_color1);
	gui.set_var_color("PortA" + suffix, addr_color1);

	gui.set_var_color("AddrB" + suffix, addr_color2);
	gui.set_var_color("PortB" + suffix, addr_color2);

}

//--------------------------------------------------------------
void Comp::setup() {
	active_ = false;
}

//--------------------------------------------------------------
void Comp::update(float dt) {
	if (active_) {
		
	}
}

//--------------------------------------------------------------
void Comp::draw() {

}

//--------------------------------------------------------------
void Comp::keyPressed(int key) {

}

//--------------------------------------------------------------
void Comp::activate(ofxKuTextGuiRemoteClient &client) {
	active_ = true;
	string addr = address_[use_address_];
	int port = port_[use_address_];
	cout << "Start connection " << id_+1 << " " << name_ << " " << addr << " : " << port << endl;
	client.setup(addr, port, PRM OSC_in_port);
}

//--------------------------------------------------------------
void Comp::deactivate(ofxKuTextGuiRemoteClient &client) {
	active_ = false;	

}

//--------------------------------------------------------------
