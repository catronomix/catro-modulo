#include "rack.hpp"

using namespace rack;


// Forward-declare the Plugin, defined in Template.cpp
extern Plugin *plugin;

// Forward-declare each Model, defined in each module source file
extern Model *modelCM1Module;
extern Model *modelCM2Module;
extern Model *modelCM3Module;

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

struct CM_Knob_big_red : SVGKnob {
	CM_Knob_big_red() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-knob_big_red.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Knob_huge_red : SVGKnob {
	CM_Knob_huge_red() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-knob_huge_red.svg")));
        shadow->opacity = 0;
	}
};
struct CM_Knob_huge_red_os : SVGKnob {
	CM_Knob_huge_red_os() {
		minAngle = 0.0*M_PI;
		maxAngle = 2.0*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-knob_huge_red.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Indicator_bigeye : SVGWidget {
	CM_Indicator_bigeye() {
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-indicator_bigeye.svg")));
	}
};

struct CM_Knob_bigeye : SVGKnob {
	CM_Knob_bigeye() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-knob_bigeye.svg")));
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

struct CM_I_def_tinybuttonL : SVGSwitch, MomentarySwitch {
	CM_I_def_tinybuttonL() {
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-input_def_tinybuttonL.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-input_def_tinybuttonL_dn.svg")));
	}
};

struct CM_I_def_tinybuttonR : SVGSwitch, MomentarySwitch {
	CM_I_def_tinybuttonR() {
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-input_def_tinybuttonR.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-input_def_tinybuttonR_dn.svg")));
	}
};

struct CM_Input_small : SVGPort {
	CM_Input_small() {
		setSVG(SVG::load(assetPlugin(plugin, "res/CM-input_small.svg")));
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

struct CM_Switch_small : SVGSwitch, ToggleSwitch {
	CM_Switch_small() {
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-TS_small_0.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-TS_small_1.svg")));
	}
};

struct CM_TryMe_button : SVGSwitch, MomentarySwitch {
	CM_TryMe_button() {
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-tryme_button.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-tryme_button_dn.svg")));
	}
};
	
struct CM_Recbutton : SVGSwitch, MomentarySwitch {
	CM_Recbutton() {
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-recbutton.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/CM-recbutton_dn.svg")));
	}
};

struct CM_Slider_big_red : SVGSlider {
	CM_Slider_big_red() {
		minHandlePos = Vec(-4, 0);
		maxHandlePos = Vec(58, 0);
		setSVGs(SVG::load(assetPlugin(plugin, "res/CM-slider_big_red_bg.svg")), SVG::load(assetPlugin(plugin, "res/CM-slider_big_red.svg")));
	}
};
