#include "CatroModulo.hpp"


//Catro-Module CM-7: vcClk--


struct CM7Module : Module {
	enum ParamIds {
		PARAM_RST,
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_BPM,
		INPUT_BPM2,
		INPUT_RST,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_CLKX1,
		OUTPUT_CLK_2,
		OUTPUT_CLK_3,
		OUTPUT_CLK_4,
		OUTPUT_CLK_5,
		OUTPUT_CLK_7,
		OUTPUT_CLK_9,
		OUTPUT_BPMX1,
		OUTPUT_BPM_2,
		OUTPUT_BPM_3,
		OUTPUT_BPM_4,
		OUTPUT_BPM_5,
		OUTPUT_BPM_7,
		OUTPUT_BPM_9,
		NUM_OUTPUTS
	};
	enum LightIds {
		ENUMS(LIGHTS_CLK, 14), 
		NUM_LIGHTS
	};

    //create objects
    //dsp::SchmittTrigger recordTrigger[16];
    CM_BpmClock clock1;
	CM_BpmClock clock2;
	CM_BpmClock clock3;
	CM_BpmClock clock4;
	CM_BpmClock clock5;
	
	CM7Module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(CM7Module::PARAM_RST, 0.0f, 1.0f, 0.0f, "");
			//initialize objects
	}
	void process(const ProcessArgs &args) override;
};

void CM7Module::process(const ProcessArgs &args) {

    //set from first bpm cv input
	clock1.setcv(inputs[INPUT_BPM].getVoltage() * 0.5);
	clock2.setcv(inputs[INPUT_BPM].getVoltage() / 3.0);
	clock3.setcv(inputs[INPUT_BPM].getVoltage() * 0.2);
	clock4.setcv(inputs[INPUT_BPM].getVoltage() / 7.0);
	clock5.setcv(inputs[INPUT_BPM].getVoltage() / 9.0);

	//generate bpm outputs before adding second cv
    outputs[OUTPUT_BPMX1].setVoltage(clock1.getcv() * 2.0);
	outputs[OUTPUT_BPM_2].setVoltage(clock1.getcv());
	outputs[OUTPUT_BPM_3].setVoltage(clock2.getcv());
	outputs[OUTPUT_BPM_4].setVoltage(clock1.getcv() * 0.5);
	outputs[OUTPUT_BPM_5].setVoltage(clock3.getcv());
	outputs[OUTPUT_BPM_7].setVoltage(clock4.getcv());
	outputs[OUTPUT_BPM_9].setVoltage(clock5.getcv());

    //add second bpm cv input
	clock1.addcv(0 - inputs[INPUT_BPM2].getVoltage() * 0.5);
	clock2.addcv(0 - inputs[INPUT_BPM2].getVoltage() / 3.0);
	clock3.addcv(0 - inputs[INPUT_BPM2].getVoltage() * 0.2);
	clock4.addcv(0 - inputs[INPUT_BPM2].getVoltage() / 7.0);
	clock5.addcv(0 - inputs[INPUT_BPM2].getVoltage() / 9.0);

    //perform reset if needed
	clock1.setReset(inputs[INPUT_RST].getVoltage() || params[PARAM_RST].getValue());
	clock2.setReset(inputs[INPUT_RST].getVoltage() || params[PARAM_RST].getValue());
	clock3.setReset(inputs[INPUT_RST].getVoltage() || params[PARAM_RST].getValue());
	clock4.setReset(inputs[INPUT_RST].getVoltage() || params[PARAM_RST].getValue());
	clock5.setReset(inputs[INPUT_RST].getVoltage() || params[PARAM_RST].getValue());

    //step clocks
	clock1.step(args.sampleTime);
	clock2.step(args.sampleTime);
	clock3.step(args.sampleTime);
	clock4.step(args.sampleTime);
	clock5.step(args.sampleTime);

    //set clock outputs
	outputs[OUTPUT_CLKX1].setVoltage(clock1.track(0) * 10.0);
	outputs[OUTPUT_CLK_2].setVoltage(clock1.track(1) * 10.0);
	outputs[OUTPUT_CLK_3].setVoltage(clock2.track(1) * 10.0);
	outputs[OUTPUT_CLK_4].setVoltage(clock1.track(2) * 10.0);
	outputs[OUTPUT_CLK_5].setVoltage(clock3.track(1) * 10.0);
	outputs[OUTPUT_CLK_7].setVoltage(clock4.track(1) * 10.0);
	outputs[OUTPUT_CLK_9].setVoltage(clock5.track(1) * 10.0);

	//set clock lights
	for (int i = 0; i < 7; i++){
		lights[2 * i + 0].setBrightnessSmooth(fmaxf(0.0f, outputs[OUTPUT_CLKX1 + i].value * 0.2f));
		lights[2 * i + 1].setBrightnessSmooth(fmaxf(0.0f, -outputs[OUTPUT_CLKX1 + i].value * 0.2f));
	}

}

struct CM7ModuleWidget : ModuleWidget {
	CM7ModuleWidget(CM7Module *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-7.svg")));

		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(2, 365)));
		
		//UNIQUE ELEMENTS
		addParam(createParam<CM_I_def_tinybuttonL>(Vec(8.7 , 330.3), module, CM7Module::PARAM_RST));
		addInput(createInput<CM_Input_def>(Vec(17.3, 330.3), module, CM7Module::INPUT_RST));

		addInput(createInput<CM_Input_bpm>(Vec(0.0 , 25.2), module, CM7Module::INPUT_BPM));
		addInput(createInput<CM_Input_bpm>(Vec(20.7 , 37.7), module, CM7Module::INPUT_BPM2));

		//clock outputs
		addOutput(createOutput<CM_Output_def>(Vec(20.7 , 74.6 ), module, CM7Module::OUTPUT_CLKX1));
		addOutput(createOutput<CM_Output_def>(Vec(20.7 , 111.5), module, CM7Module::OUTPUT_CLK_2));
		addOutput(createOutput<CM_Output_def>(Vec(20.7 , 148.3), module, CM7Module::OUTPUT_CLK_3));
		addOutput(createOutput<CM_Output_def>(Vec(20.7 , 185.2), module, CM7Module::OUTPUT_CLK_4));
		addOutput(createOutput<CM_Output_def>(Vec(20.7 , 222.0), module, CM7Module::OUTPUT_CLK_5));
		addOutput(createOutput<CM_Output_def>(Vec(20.7 , 258.9), module, CM7Module::OUTPUT_CLK_7));
		addOutput(createOutput<CM_Output_def>(Vec(20.7 , 295.8), module, CM7Module::OUTPUT_CLK_9));

		//bpm cv outputs
		addOutput(createOutput<CM_Output_bpm>(Vec(0 , 61.3) , module, CM7Module::OUTPUT_BPMX1));
		addOutput(createOutput<CM_Output_bpm>(Vec(0 , 98.2) , module, CM7Module::OUTPUT_BPM_2));
		addOutput(createOutput<CM_Output_bpm>(Vec(0 , 135.0), module, CM7Module::OUTPUT_BPM_3));
		addOutput(createOutput<CM_Output_bpm>(Vec(0 , 171.9), module, CM7Module::OUTPUT_BPM_4));
		addOutput(createOutput<CM_Output_bpm>(Vec(0 , 208.7), module, CM7Module::OUTPUT_BPM_5));
		addOutput(createOutput<CM_Output_bpm>(Vec(0 , 245.6), module, CM7Module::OUTPUT_BPM_7));
		addOutput(createOutput<CM_Output_bpm>(Vec(0 , 282.5), module, CM7Module::OUTPUT_BPM_9));

		//clock lights
		addChild(createLight<TinyLight<GreenRedLight>>(Vec(41.0 , 74.6  + 21.0), module, CM7Module::LIGHTS_CLK));
		addChild(createLight<TinyLight<GreenRedLight>>(Vec(41.0 , 111.5 + 21.0), module, CM7Module::LIGHTS_CLK + 2));
		addChild(createLight<TinyLight<GreenRedLight>>(Vec(41.0 , 148.3 + 21.0), module, CM7Module::LIGHTS_CLK + 4));
		addChild(createLight<TinyLight<GreenRedLight>>(Vec(41.0 , 185.2 + 21.0), module, CM7Module::LIGHTS_CLK + 6));
		addChild(createLight<TinyLight<GreenRedLight>>(Vec(41.0 , 222.0 + 21.0), module, CM7Module::LIGHTS_CLK + 8));
		addChild(createLight<TinyLight<GreenRedLight>>(Vec(41.0 , 258.9 + 21.0), module, CM7Module::LIGHTS_CLK + 10));
		addChild(createLight<TinyLight<GreenRedLight>>(Vec(41.0 , 295.8 + 21.0), module, CM7Module::LIGHTS_CLK + 12));
	
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per pluginInstance, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM7Module = createModel<CM7Module, CM7ModuleWidget>("CatroModulo_CM-7");
