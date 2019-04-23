#include "CatroModulo.hpp"


//Catro-Module CM-5: BPM2CV


struct CM5Module : Module {
	enum ParamIds {
		PARAM_RST,
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_BPM,
		INPUT_RST,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_CLKX1,
		OUTPUT_CLKX2,
		OUTPUT_CLKX3,
		OUTPUT_CLKX4,
		OUTPUT_CLKX5,
		OUTPUT_CLKX6,
		OUTPUT_CLKX7,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

    //create objects
    //SchmittTrigger recordTrigger[16];
    CM_BpmClock clock1;
	CM_BpmClock clock2;
	CM_BpmClock clock3;
	CM_BpmClock clock4;
	
	CM5Module() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
			//initialize objects
	}
	void step() override;
};

void CM5Module::step() {

	clock1.setcv(inputs[INPUT_BPM].value * 2.0);
	clock2.setcv(inputs[INPUT_BPM].value * 3.0);
	clock3.setcv(inputs[INPUT_BPM].value * 5.0);
	clock4.setcv(inputs[INPUT_BPM].value * 7.0);

	clock1.setReset(inputs[INPUT_RST].value || params[PARAM_RST].value);
	clock2.setReset(inputs[INPUT_RST].value || params[PARAM_RST].value);
	clock3.setReset(inputs[INPUT_RST].value || params[PARAM_RST].value);
	clock4.setReset(inputs[INPUT_RST].value || params[PARAM_RST].value);

	clock1.step(engineGetSampleTime());
	clock2.step(engineGetSampleTime());
	clock3.step(engineGetSampleTime());
	clock4.step(engineGetSampleTime());

	outputs[OUTPUT_CLKX1].value = clock1.track(2) * 10.0;
	outputs[OUTPUT_CLKX2].value = clock1.track(1) * 10.0;
	outputs[OUTPUT_CLKX3].value = clock2.track(1) * 10.0;
	outputs[OUTPUT_CLKX4].value = clock1.track(0) * 10.0;
	outputs[OUTPUT_CLKX5].value = clock3.track(1) * 10.0;
	outputs[OUTPUT_CLKX6].value = clock2.track(0) * 10.0;
	outputs[OUTPUT_CLKX7].value = clock4.track(1) * 10.0;

}

struct CM5ModuleWidget : ModuleWidget {
	CM5ModuleWidget(CM5Module *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/CM-5.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(2, 365)));
		
		//UNIQUE ELEMENTS
		addParam(ParamWidget::create<CM_I_def_tinybuttonL>(Vec(8.7 , 330.3), module, CM5Module::PARAM_RST, 0.0f, 1.0f, 0.0f));
		addInput(Port::create<CM_Input_def>(Vec(17.3, 330.3), Port::INPUT, module, CM5Module::INPUT_RST));

		addInput(Port::create<CM_Input_bpm>(Vec(10.9 , 29.4), Port::INPUT, module, CM5Module::INPUT_BPM));

		addOutput(Port::create<CM_Output_def>(Vec(10.9 , 66.9), Port::OUTPUT, module, CM5Module::OUTPUT_CLKX1));
		addOutput(Port::create<CM_Output_def>(Vec(10.9 , 104.3), Port::OUTPUT, module, CM5Module::OUTPUT_CLKX2));
		addOutput(Port::create<CM_Output_def>(Vec(10.9 , 141.8), Port::OUTPUT, module, CM5Module::OUTPUT_CLKX3));
		addOutput(Port::create<CM_Output_def>(Vec(10.9 , 179.2), Port::OUTPUT, module, CM5Module::OUTPUT_CLKX4));
		addOutput(Port::create<CM_Output_def>(Vec(10.9 , 216.7), Port::OUTPUT, module, CM5Module::OUTPUT_CLKX5));
		addOutput(Port::create<CM_Output_def>(Vec(10.9 , 254.2), Port::OUTPUT, module, CM5Module::OUTPUT_CLKX6));
		addOutput(Port::create<CM_Output_def>(Vec(10.9 , 291.6), Port::OUTPUT, module, CM5Module::OUTPUT_CLKX7));
	
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM5Module = Model::create<CM5Module, CM5ModuleWidget>("CatroModulo", "CatroModulo_CM-5", "C/M5 : vcClk++", CLOCK_TAG);
