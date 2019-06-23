#include "CatroModulo.hpp"


//Catro-Module CM-6: 1hp blank

struct CM6Module : Module {

	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	CM6Module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}
	void process(const ProcessArgs &args) override;
};

void CM6Module::process(const ProcessArgs &args) {
}

struct CM6ModuleWidget : ModuleWidget {

	CM6ModuleWidget(CM6Module *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-6.svg")));

		addChild(createWidget<ScrewSilver>(Vec(1, 0)));
		addChild(createWidget<ScrewSilver>(Vec(1, 365)));

	}
};

Model *modelCM6Module = createModel<CM6Module, CM6ModuleWidget>("CatroModulo_CM-6");
