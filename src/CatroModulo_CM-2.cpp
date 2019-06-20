#include "CatroModulo.hpp"

//Catro-Module 8xatn
//parts of code copied from VCV's 8VERT module from the Fundamental pack by Andew Belt.


struct CM2Module : Module {
	enum ParamIds {
		ENUMS(PARAMS_ATN, 8),
		ENUMS(PARAMS_OFF, 8),
		PARAMS_X2,
		NUM_PARAMS
	};
	enum InputIds {
		ENUMS(INPUTS_IN, 8),
		ENUMS(INPUTS_ATN, 8),
		ENUMS(INPUTS_OFF, 8),
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS = 9
	};
	enum LightIds {
		NUM_LIGHTS = 0
	};
	int overdrive = 0;

	CM2Module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu
};

void CM2Module::step() {
	float mixOut = 0.0f;
	int numconnect = 0;
	overdrive = params[PARAMS_X2].value;

	for (int i = 0; i < 8; i++) {
		numconnect += (inputs[INPUTS_IN + i].active) ? 1 : 0;
		float out = 0.0f;

		//cv process
		float attn = (inputs[INPUTS_ATN + i].active) ? clamp(inputs[INPUTS_ATN].value, -10.0, 10.0) * 0.1 * params[PARAMS_ATN + i].value : params[PARAMS_ATN + i].value;
		float offset = (inputs[INPUTS_OFF + i].active) ? clamp(inputs[INPUTS_OFF].value, -10.0, 10.0) + params[PARAMS_OFF + i].value : params[PARAMS_OFF + i].value;

		if (inputs[INPUTS_IN + i].active == true || outputs[i].active == true) {
			if (inputs[INPUTS_IN + i].active == true) {
				out = clamp((inputs[INPUTS_IN + i].value * attn + offset), -10.0f, 10.0f);
				mixOut += out;
			} else {
				out = clamp(attn * offset, -10.0f, 10.0f);
			}
			outputs[i].value = out * overdrive;
		}
		if (numconnect > 0) {
			outputs[8].value = mixOut * overdrive / numconnect;
		}else{
			outputs[8].value = 0.0f;
		}
	}
}

struct CM2ModuleWidget : ModuleWidget {
	CM2ModuleWidget(CM2Module *module) {
		setModule(module);
		setPanel(SVG::load(assetPlugin(pluginInstance, "res/CM-2.svg")));

	addChild(createWidget<ScrewSilver>(Vec(15, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 0)));
	addChild(createWidget<ScrewSilver>(Vec(15, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 365)));
	//grid
	const float gridrowjacks[8] = {38.4, 77.2, 116.0, 154.7, 193.5, 232.3, 271.0, 309.8};

	//ATN knobs
	addParam(createParam<CM_Knob_big_attn>(Vec(49.0, gridrowjacks[0] - 16.5), module, CM2Module::PARAMS_ATN + 0, -1.0f, 1.0f, 0.0f));
	addParam(createParam<CM_Knob_big_attn>(Vec(49.0, gridrowjacks[1] - 16.5), module, CM2Module::PARAMS_ATN + 1, -1.0f, 1.0f, 0.0f));
	addParam(createParam<CM_Knob_big_attn>(Vec(49.0, gridrowjacks[2] - 16.5), module, CM2Module::PARAMS_ATN + 2, -1.0f, 1.0f, 0.0f));
	addParam(createParam<CM_Knob_big_attn>(Vec(49.0, gridrowjacks[3] - 16.5), module, CM2Module::PARAMS_ATN + 3, -1.0f, 1.0f, 0.0f));
	addParam(createParam<CM_Knob_big_attn>(Vec(49.0, gridrowjacks[4] - 16.5), module, CM2Module::PARAMS_ATN + 4, -1.0f, 1.0f, 0.0f));
	addParam(createParam<CM_Knob_big_attn>(Vec(49.0, gridrowjacks[5] - 16.5), module, CM2Module::PARAMS_ATN + 5, -1.0f, 1.0f, 0.0f));
	addParam(createParam<CM_Knob_big_attn>(Vec(49.0, gridrowjacks[6] - 16.5), module, CM2Module::PARAMS_ATN + 6, -1.0f, 1.0f, 0.0f));
	addParam(createParam<CM_Knob_big_attn>(Vec(49.0, gridrowjacks[7] - 16.5), module, CM2Module::PARAMS_ATN + 7, -1.0f, 1.0f, 0.0f));

	//ATN CV
	addInput(createPort<CM_Input_small>(Vec(32.0, gridrowjacks[0] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_ATN + 0));
	addInput(createPort<CM_Input_small>(Vec(32.0, gridrowjacks[1] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_ATN + 1));
	addInput(createPort<CM_Input_small>(Vec(32.0, gridrowjacks[2] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_ATN + 2));
	addInput(createPort<CM_Input_small>(Vec(32.0, gridrowjacks[3] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_ATN + 3));
	addInput(createPort<CM_Input_small>(Vec(32.0, gridrowjacks[4] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_ATN + 4));
	addInput(createPort<CM_Input_small>(Vec(32.0, gridrowjacks[5] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_ATN + 5));
	addInput(createPort<CM_Input_small>(Vec(32.0, gridrowjacks[6] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_ATN + 6));
	addInput(createPort<CM_Input_small>(Vec(32.0, gridrowjacks[7] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_ATN + 7));

	//OFFSET knobs
	addParam(createParam<CM_Knob_big_offset>(Vec(98.5, gridrowjacks[0] - 16.5), module, CM2Module::PARAMS_OFF + 0, -5.0f, 5.0f, 0.0f));
	addParam(createParam<CM_Knob_big_offset>(Vec(98.5, gridrowjacks[1] - 16.5), module, CM2Module::PARAMS_OFF + 1, -5.0f, 5.0f, 0.0f));
	addParam(createParam<CM_Knob_big_offset>(Vec(98.5, gridrowjacks[2] - 16.5), module, CM2Module::PARAMS_OFF + 2, -5.0f, 5.0f, 0.0f));
	addParam(createParam<CM_Knob_big_offset>(Vec(98.5, gridrowjacks[3] - 16.5), module, CM2Module::PARAMS_OFF + 3, -5.0f, 5.0f, 0.0f));
	addParam(createParam<CM_Knob_big_offset>(Vec(98.5, gridrowjacks[4] - 16.5), module, CM2Module::PARAMS_OFF + 4, -5.0f, 5.0f, 0.0f));
	addParam(createParam<CM_Knob_big_offset>(Vec(98.5, gridrowjacks[5] - 16.5), module, CM2Module::PARAMS_OFF + 5, -5.0f, 5.0f, 0.0f));
	addParam(createParam<CM_Knob_big_offset>(Vec(98.5, gridrowjacks[6] - 16.5), module, CM2Module::PARAMS_OFF + 6, -5.0f, 5.0f, 0.0f));
	addParam(createParam<CM_Knob_big_offset>(Vec(98.5, gridrowjacks[7] - 16.5), module, CM2Module::PARAMS_OFF + 7, -5.0f, 5.0f, 0.0f));

	//OFFSET CV
	addInput(createPort<CM_Input_small>(Vec(81.3, gridrowjacks[0] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_OFF + 0));
	addInput(createPort<CM_Input_small>(Vec(81.3, gridrowjacks[1] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_OFF + 1));
	addInput(createPort<CM_Input_small>(Vec(81.3, gridrowjacks[2] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_OFF + 2));
	addInput(createPort<CM_Input_small>(Vec(81.3, gridrowjacks[3] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_OFF + 3));
	addInput(createPort<CM_Input_small>(Vec(81.3, gridrowjacks[4] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_OFF + 4));
	addInput(createPort<CM_Input_small>(Vec(81.3, gridrowjacks[5] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_OFF + 5));
	addInput(createPort<CM_Input_small>(Vec(81.3, gridrowjacks[6] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_OFF + 6));
	addInput(createPort<CM_Input_small>(Vec(81.3, gridrowjacks[7] + 3.4), PortWidget::INPUT, module, CM2Module::INPUTS_OFF + 7));

	//Signal IN
	addInput(createPort<CM_Input_def>(Vec(5.0, gridrowjacks[0]), PortWidget::INPUT, module, CM2Module::INPUTS_IN + 0));
	addInput(createPort<CM_Input_def>(Vec(5.0, gridrowjacks[1]), PortWidget::INPUT, module, CM2Module::INPUTS_IN + 1));
	addInput(createPort<CM_Input_def>(Vec(5.0, gridrowjacks[2]), PortWidget::INPUT, module, CM2Module::INPUTS_IN + 2));
	addInput(createPort<CM_Input_def>(Vec(5.0, gridrowjacks[3]), PortWidget::INPUT, module, CM2Module::INPUTS_IN + 3));
	addInput(createPort<CM_Input_def>(Vec(5.0, gridrowjacks[4]), PortWidget::INPUT, module, CM2Module::INPUTS_IN + 4));
	addInput(createPort<CM_Input_def>(Vec(5.0, gridrowjacks[5]), PortWidget::INPUT, module, CM2Module::INPUTS_IN + 5));
	addInput(createPort<CM_Input_def>(Vec(5.0, gridrowjacks[6]), PortWidget::INPUT, module, CM2Module::INPUTS_IN + 6));
	addInput(createPort<CM_Input_def>(Vec(5.0, gridrowjacks[7]), PortWidget::INPUT, module, CM2Module::INPUTS_IN + 7));

	//Signal OUT
	addOutput(createPort<CM_Output_def>(Vec(134.6, gridrowjacks[0]), PortWidget::OUTPUT, module, 0));
	addOutput(createPort<CM_Output_def>(Vec(134.6, gridrowjacks[1]), PortWidget::OUTPUT, module, 1));
	addOutput(createPort<CM_Output_def>(Vec(134.6, gridrowjacks[2]), PortWidget::OUTPUT, module, 2));
	addOutput(createPort<CM_Output_def>(Vec(134.6, gridrowjacks[3]), PortWidget::OUTPUT, module, 3));
	addOutput(createPort<CM_Output_def>(Vec(134.6, gridrowjacks[4]), PortWidget::OUTPUT, module, 4));
	addOutput(createPort<CM_Output_def>(Vec(134.6, gridrowjacks[5]), PortWidget::OUTPUT, module, 5));
	addOutput(createPort<CM_Output_def>(Vec(134.6, gridrowjacks[6]), PortWidget::OUTPUT, module, 6));
	addOutput(createPort<CM_Output_def>(Vec(134.6, gridrowjacks[7]), PortWidget::OUTPUT, module, 7));

	addOutput(createPort<CM_Output_small>(Vec(98.1, 336.3), PortWidget::OUTPUT, module, 8));
	addParam(createParam<CM_Switch_small>(Vec(3.0, 339.4), module, CM2Module::PARAMS_X2, 1.0f, 2.0f, 1.0f));
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per pluginInstance, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM2Module = createModel<CM2Module, CM2ModuleWidget>("CatroModulo_CM-2");
