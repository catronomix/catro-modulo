#include "rack.hpp"

using namespace rack;


// Forward-declare the Plugin, defined in Template.cpp
extern Plugin *plugin;

// Forward-declare each Model, defined in each module source file
extern Model *modelCM1Module;
extern Model *modelCM2Module;

struct CM_Knob_small_def : SVGKnob {
	CM_Knob_small_def() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-knob_small_def.svg")));
        shadow->opacity = 0;
        
	}
};

struct CM_Knob_small_def_half : SVGKnob {
	CM_Knob_small_def_half() {
		minAngle = -0.5*M_PI;
		maxAngle = 0.5*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-knob_small_def.svg")));
        shadow->opacity = 0;
        
	}
};

struct CM_Knob_small_red : SVGKnob {
	CM_Knob_small_red() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-knob_small_red.svg")));
        shadow->opacity = 0;
        
	}
};

struct CM_Knob_big_def : SVGKnob {
	CM_Knob_big_def() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-knob_big_def.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Pot1_small : SVGScrew {
	CM_Pot1_small() {
		sw->setSVG(SVG::load(assetPlugin(plugin, "res/CM-pot1_small.svg")));
		box.size = sw->box.size;
	}
};

struct CM_Pot1_big : SVGScrew {
	CM_Pot1_big() {
		sw->setSVG(SVG::load(assetPlugin(plugin, "res/CM-pot1_big.svg")));
		box.size = sw->box.size;
        
	}
};

struct CM_Input_def : SVGPort {
	CM_Input_def() {
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-input_def.svg")));
        shadow->opacity = 0;
	}
};



struct CM_Output_def : SVGPort {
	CM_Output_def() {
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-output_def.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Output_small : SVGPort {
	CM_Output_small() {
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-output_small.svg")));
        shadow->opacity = 0;
	}
};