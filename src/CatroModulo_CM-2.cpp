#include "CatroModulo.hpp"

//Catro-Module 8xatn
//parts of code copied from VCV's 8VERT module from the Fundamental pack by Andew Belt.


struct CM2Module : Module {
	enum ParamIds {
		NUM_PARAMS = 16
	};
	enum InputIds {
		NUM_INPUTS = 8
	};
	enum OutputIds {
		NUM_OUTPUTS = 9
	};
	enum LightIds {
		NUM_LIGHTS = 16
	};

	CM2Module() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu
};

void CM2Module::step() {
	float mixOut = 0.0f;
	int numconnect = 0;

	for (int i = 0; i < 8; i++) {
		numconnect += (inputs[i].active) ? 1 : 0;
		float out = 0.0f;

		if (inputs[i].active == true || outputs[i].active == true) {
			int j = i + 8;
			if (inputs[i].active == true) {
				out = clamp(inputs[i].value * params[i].value + params[j].value * 5.0f, -10.0f, 10.0f);
				mixOut += out;
			} else {
				out = clamp(params[i].value + params[j].value * 5.0f, -10.0f, 10.0f);
			}
			outputs[i].value = out;
			
			lights[2*i + 0].setBrightnessSmooth(fmaxf(0.0f, out * 0.2f));
			lights[2*i + 1].setBrightnessSmooth(fmaxf(0.0f, -out * 0.2f));
		}
		if (numconnect > 0) {
			outputs[8].value = mixOut / numconnect;
		}else{
			outputs[8].value = 0.0f;
		}
	}
}

struct CM2ModuleWidget : ModuleWidget {
	CM2ModuleWidget(CM2Module *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/CM-2.svg")));

	addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));
	//grid
	const float gridrowjacks[8] = {35.5, 74.3, 113.1, 151.9, 190.7, 229.5, 268.2, 307};

	
	//LEFT ROW POTS
	addChild(Widget::create<CM_Pot1_small>(Vec(43.5, gridrowjacks[0] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(43.5, gridrowjacks[1] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(43.5, gridrowjacks[2] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(43.5, gridrowjacks[3] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(43.5, gridrowjacks[4] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(43.5, gridrowjacks[5] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(43.5, gridrowjacks[6] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(43.5, gridrowjacks[7] - 4.8)));

	// RIGHT POTS)
	addChild(Widget::create<CM_Pot1_small>(Vec(86.5, gridrowjacks[0] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(86.5, gridrowjacks[1] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(86.5, gridrowjacks[2] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(86.5, gridrowjacks[3] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(86.5, gridrowjacks[4] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(86.5, gridrowjacks[5] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(86.5, gridrowjacks[6] - 4.8)));
	addChild(Widget::create<CM_Pot1_small>(Vec(86.5, gridrowjacks[7] - 4.8)));

	//LEFT ROW KNOBS
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(43.5, gridrowjacks[0] - 4.8), module, 0, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(43.5, gridrowjacks[1] - 4.8), module, 1, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(43.5, gridrowjacks[2] - 4.8), module, 2, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(43.5, gridrowjacks[3] - 4.8), module, 3, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(43.5, gridrowjacks[4] - 4.8), module, 4, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(43.5, gridrowjacks[5] - 4.8), module, 5, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(43.5, gridrowjacks[6] - 4.8), module, 6, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(43.5, gridrowjacks[7] - 4.8), module, 7, -1.0f, 1.0f, 0.0f));

	//RIGHT ROW KNOBS
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(86.5, gridrowjacks[0] - 4.8), module, 8, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(86.5, gridrowjacks[1] - 4.8), module, 9, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(86.5, gridrowjacks[2] - 4.8), module, 10, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(86.5, gridrowjacks[3] - 4.8), module, 11, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(86.5, gridrowjacks[4] - 4.8), module, 12, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(86.5, gridrowjacks[5] - 4.8), module, 13, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(86.5, gridrowjacks[6] - 4.8), module, 14, -1.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<CM_Knob_small_def>(Vec(86.5, gridrowjacks[7] - 4.8), module, 15, -1.0f, 1.0f, 0.0f));

	addInput(Port::create<CM_Input_def>(Vec(9.6, gridrowjacks[0]), Port::INPUT, module, 0));
	addInput(Port::create<CM_Input_def>(Vec(9.6, gridrowjacks[1]), Port::INPUT, module, 1));
	addInput(Port::create<CM_Input_def>(Vec(9.6, gridrowjacks[2]), Port::INPUT, module, 2));
	addInput(Port::create<CM_Input_def>(Vec(9.6, gridrowjacks[3]), Port::INPUT, module, 3));
	addInput(Port::create<CM_Input_def>(Vec(9.6, gridrowjacks[4]), Port::INPUT, module, 4));
	addInput(Port::create<CM_Input_def>(Vec(9.6, gridrowjacks[5]), Port::INPUT, module, 5));
	addInput(Port::create<CM_Input_def>(Vec(9.6, gridrowjacks[6]), Port::INPUT, module, 6));
	addInput(Port::create<CM_Input_def>(Vec(9.6, gridrowjacks[7]), Port::INPUT, module, 7));

	addOutput(Port::create<CM_Output_def>(Vec(131, gridrowjacks[0]), Port::OUTPUT, module, 0));
	addOutput(Port::create<CM_Output_def>(Vec(131, gridrowjacks[1]), Port::OUTPUT, module, 1));
	addOutput(Port::create<CM_Output_def>(Vec(131, gridrowjacks[2]), Port::OUTPUT, module, 2));
	addOutput(Port::create<CM_Output_def>(Vec(131, gridrowjacks[3]), Port::OUTPUT, module, 3));
	addOutput(Port::create<CM_Output_def>(Vec(131, gridrowjacks[4]), Port::OUTPUT, module, 4));
	addOutput(Port::create<CM_Output_def>(Vec(131, gridrowjacks[5]), Port::OUTPUT, module, 5));
	addOutput(Port::create<CM_Output_def>(Vec(131, gridrowjacks[6]), Port::OUTPUT, module, 6));
	addOutput(Port::create<CM_Output_def>(Vec(131, gridrowjacks[7]), Port::OUTPUT, module, 7));

	addOutput(Port::create<CM_Output_small>(Vec(98.1, 336.3), Port::OUTPUT, module, 8));

	addChild(ModuleLightWidget::create<TinyLight<GreenRedLight>>(Vec(160, gridrowjacks[0] + 10), module, 0));
	addChild(ModuleLightWidget::create<TinyLight<GreenRedLight>>(Vec(160, gridrowjacks[1] + 10), module, 2));
	addChild(ModuleLightWidget::create<TinyLight<GreenRedLight>>(Vec(160, gridrowjacks[2] + 10), module, 4));
	addChild(ModuleLightWidget::create<TinyLight<GreenRedLight>>(Vec(160, gridrowjacks[3] + 10), module, 6));
	addChild(ModuleLightWidget::create<TinyLight<GreenRedLight>>(Vec(160, gridrowjacks[4] + 10), module, 8));
	addChild(ModuleLightWidget::create<TinyLight<GreenRedLight>>(Vec(160, gridrowjacks[5] + 10), module, 10));
	addChild(ModuleLightWidget::create<TinyLight<GreenRedLight>>(Vec(160, gridrowjacks[6] + 10), module, 12));
	addChild(ModuleLightWidget::create<TinyLight<GreenRedLight>>(Vec(160, gridrowjacks[7] + 10), module, 14));

	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM2Module = Model::create<CM2Module, CM2ModuleWidget>("CatroModulo", "CatroModulo_CM-2", "C/M2 : 8xatn", ATTENUATOR_TAG);
