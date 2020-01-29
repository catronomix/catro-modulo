#include "CatroModulo.hpp"
#include "CM_helpers.hpp"

//Catro-Module CM-8: aAvsBb

struct CM8Module : Module {

	enum ParamIds {
		PARAM__a,
		PARAM__b,
        PARAM_CIA,
		PARAM_BMODE,
		PARAM_NORMALIZE,
		NUM_PARAMS
	};
	enum InputIds {
		INPUT__a,
		INPUT__b,
		INPUT_A,
		INPUT_B,
		INPUT_SNH,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT__a,
		OUTPUT__b,
		OUTPUT_ALTB,
		OUTPUT_BLTA,
		OUTPUT_AISB,
		OUTPUT_ANTB,
		OUTPUT_ACLM,
		OUTPUT_BCLM,
		OUTPUT_AFLD,
		OUTPUT_BFLD,
        OUTPUT_ALO,
        OUTPUT_BLO,
        OUTPUT_AHI,
        OUTPUT_BHI,
        OUTPUT_ARNG,
        OUTPUT_BRNG,
		NUM_OUTPUTS
	};
	enum LightIds {
        LIGHT_ALTB,
		LIGHT_BLTA,
		LIGHT_ACLM,
		LIGHT_BCLM,
		LIGHT_AFLD,
		LIGHT_BFLD,
        LIGHT_ALO,
        LIGHT_BLO,
        LIGHT_AHI,
        LIGHT_BHI,
        LIGHT_ARNG,
        LIGHT_BRNG,
		NUM_LIGHTS
	};

   //initializations
   float lo;
   float hi;
   int cia;
   dsp::SchmittTrigger snhTrigger;
   float lastA;
   float lastB;
   float currentA;
   float currentB;
   float binA;
   float binB;
   bool binarymode;
	
	CM8Module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(CM8Module::PARAM__a, -10.0, 10.0, 0.0f, "lower treshold", "V");
		configParam(CM8Module::PARAM__b, -10.0, 10.0, 0.0f, "upper treshold", "V");
		configParam(CM8Module::PARAM_CIA, 0.0f, 2.0f, 0.0f, "centered < inversing > additive");
		configParam(CM8Module::PARAM_BMODE, 0.0f, 1.0f, 0.0f, "binary mode");
		configParam(CM8Module::PARAM_NORMALIZE, 0.0f, 1.0f, 0.0f, "normalize waveshapers");

		srand(time(NULL));
		cia = 1;
		lo = hi = lastA = lastB = currentA = currentB = binA = binB = 0.0;
		binarymode = false;
	}
	void process(const ProcessArgs &args) override;
};

void CM8Module::process(const ProcessArgs &args) {
	// set mode
	cia = params[PARAM_CIA].getValue();


	//set limits
		
		if (cia == 0){
			lo = (inputs[INPUT__a].isConnected()) ? (inputs[INPUT__a].getVoltage() * 0.1) * params[PARAM__a].getValue() : params[PARAM__a].getValue();
			hi = (inputs[INPUT__b].isConnected()) ? (inputs[INPUT__b].getVoltage() * 0.1) * params[PARAM__b].getValue() : params[PARAM__b].getValue();
			if (lo > hi){
				hi = (lo + hi) * 0.5;
				lo = hi;
			}
			outputs[OUTPUT__a].setVoltage(lo);
			outputs[OUTPUT__b].setVoltage(hi);
		}
		if (cia == 1){
			lo = (inputs[INPUT__a].isConnected()) ? (inputs[INPUT__a].getVoltage() * 0.1) * params[PARAM__a].getValue() : params[PARAM__a].getValue();
			hi = (inputs[INPUT__b].isConnected()) ? (inputs[INPUT__b].getVoltage() * 0.1) * params[PARAM__b].getValue() : params[PARAM__b].getValue();
			outputs[OUTPUT__a].setVoltage(lo);
			outputs[OUTPUT__b].setVoltage(hi);
			if (lo > hi){
			std::swap(lo, hi);
			}
		}
		if (cia == 2){
			lo = (inputs[INPUT__a].isConnected()) ? (inputs[INPUT__a].getVoltage() * 0.1) * params[PARAM__a].getValue() : params[PARAM__a].getValue();
			hi = lo + ((inputs[INPUT__b].isConnected()) ? (inputs[INPUT__b].getVoltage() * 0.1) * params[PARAM__b].getValue() : params[PARAM__b].getValue());
			outputs[OUTPUT__a].setVoltage(lo);
			outputs[OUTPUT__b].setVoltage(hi);
			if (lo > hi){
			std::swap(lo, hi);
			}
		}

	currentA = inputs[INPUT_A].getVoltage();
	currentB = inputs[INPUT_B].getVoltage();

	//handle empty inputs
	if (! inputs[INPUT_A].isConnected()) currentA = (inputs[INPUT_B].isConnected()) ? cm_gauss(5.0, currentB) : cm_gauss(10.0);
	if (! inputs[INPUT_B].isConnected()) currentB = (inputs[INPUT_A].isConnected()) ? cm_gauss(5.0, currentA) : cm_gauss(10.0);

	//sample and hold
	if (inputs[INPUT_SNH].isConnected())
	{
		if (snhTrigger.process(inputs[INPUT_SNH].getVoltage()))
		{
			lastA = currentA;
			lastB = currentB;
		}
		currentA = lastA;
		currentB = lastB;
	}

	binA = currentA;
	binB = currentB;
	if (params[PARAM_BMODE].value == 1)
	{
		binA = (binA > 0) ? 10.0 : 0.0;
		binB = (binB > 0) ? 10.0 : 0.0;
	}

	//A
	outputs[OUTPUT_ALTB].setVoltage((binA > binB) * 10.0);
	outputs[OUTPUT_AISB].setVoltage((binA == binB) * 10.0);
	outputs[OUTPUT_ACLM].setVoltage(cm_clamp(binA, lo, hi, params[PARAM_NORMALIZE].getValue()));
	outputs[OUTPUT_AFLD].setVoltage(cm_fold(binA, lo, hi, params[PARAM_NORMALIZE].getValue()));
	outputs[OUTPUT_ALO].setVoltage((currentA < lo) * 10.0);
	outputs[OUTPUT_AHI].setVoltage((currentA > hi) * 10.0);
	outputs[OUTPUT_ARNG].setVoltage((currentA >= lo && currentA <= hi) * 10.0);

	//B
	outputs[OUTPUT_BLTA].setVoltage((binA < binB) * 10.0);
	outputs[OUTPUT_ANTB].setVoltage(!(binA == binB) * 10.0);
	outputs[OUTPUT_BCLM].setVoltage(cm_clamp(binB, lo, hi, params[PARAM_NORMALIZE].getValue()));
	outputs[OUTPUT_BFLD].setVoltage(cm_fold(binB, lo, hi, params[PARAM_NORMALIZE].getValue()));
	outputs[OUTPUT_BLO].setVoltage((currentB < lo) * 10.0);
	outputs[OUTPUT_BHI].setVoltage((currentB > hi) * 10.0);
	outputs[OUTPUT_BRNG].setVoltage((currentB >= lo && currentB <= hi) * 10.0);


}

struct CM8ModuleWidget : ModuleWidget {

	CM8ModuleWidget(CM8Module *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-8.svg")));

		//addChild(createWidget<ScrewSilver>(Vec(30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 16, 0)));
		addChild(createWidget<ScrewSilver>(Vec(5, 365)));
		// addChild(createWidget<ScrewSilver>(Vec(box.size.x - 60, 365)));

		//widget items
        addParam(createParam<CM_Knob_big_def_tt>(Vec(34.2 , 18.0), module, CM8Module::PARAM__a));
		addParam(createParam<CM_Knob_big_def_tt>(Vec(5.4 , 58.0), module, CM8Module::PARAM__b));

		addInput(createInput<CM_Input_small>(Vec(8.4 , 18.0), module, CM8Module::INPUT__a));
        addInput(createInput<CM_Input_small>(Vec(50.0 , 57.1), module, CM8Module::INPUT__b));

        addOutput(createOutput<CM_Output_small>(Vec(8.4 , 39.1), module, CM8Module::OUTPUT__a));
        addOutput(createOutput<CM_Output_small>(Vec(50.0 , 78.3), module, CM8Module::OUTPUT__b));

		addParam(createParam<CM_Switch_small_3>(Vec(16.4, 103.3), module, CM8Module::PARAM_CIA));
		addParam(createParam<CM_Ledbutton_mini>(Vec(5.0, 117.2), module, CM8Module::PARAM_BMODE));
		addInput(createInput<CM_Input_small>(Vec(54.0 , 112.7), module, CM8Module::INPUT_SNH));
		addParam(createParam<CM_8_normalizebutton>(Vec(25.0 , 241.3), module, CM8Module::PARAM_NORMALIZE));

		float a = 5.4;
		float b = 46.0;
		float c[8] = {138.8, 166.0, 193.2, 221.9, 249.1, 277.1, 304.3, 331.5};

		addInput(createInput<CM_Input_def>(Vec(a, c[0]), module, CM8Module::INPUT_A));
		addInput(createInput<CM_Input_def>(Vec(b, c[0]), module, CM8Module::INPUT_B));

		addOutput(createOutput<CM_Output_def>(Vec(a , c[1]), module, CM8Module::OUTPUT_ALTB));
		addOutput(createOutput<CM_Output_def>(Vec(b , c[1]), module, CM8Module::OUTPUT_BLTA));

		addOutput(createOutput<CM_Output_def>(Vec(a , c[2]), module, CM8Module::OUTPUT_AISB));
		addOutput(createOutput<CM_Output_def>(Vec(b , c[2]), module, CM8Module::OUTPUT_ANTB));

		addOutput(createOutput<CM_Output_def>(Vec(a , c[3]), module, CM8Module::OUTPUT_ACLM));
		addOutput(createOutput<CM_Output_def>(Vec(b , c[3]), module, CM8Module::OUTPUT_BCLM));

		addOutput(createOutput<CM_Output_def>(Vec(a , c[4]), module, CM8Module::OUTPUT_AFLD));
		addOutput(createOutput<CM_Output_def>(Vec(b , c[4]), module, CM8Module::OUTPUT_BFLD));

		addOutput(createOutput<CM_Output_def>(Vec(a , c[5]), module, CM8Module::OUTPUT_ALO));
		addOutput(createOutput<CM_Output_def>(Vec(b , c[5]), module, CM8Module::OUTPUT_BLO));

		addOutput(createOutput<CM_Output_def>(Vec(a , c[6]), module, CM8Module::OUTPUT_AHI));
		addOutput(createOutput<CM_Output_def>(Vec(b , c[6]), module, CM8Module::OUTPUT_BHI));

		addOutput(createOutput<CM_Output_def>(Vec(a , c[7]), module, CM8Module::OUTPUT_ARNG));
		addOutput(createOutput<CM_Output_def>(Vec(b , c[7]), module, CM8Module::OUTPUT_BRNG));

	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per pluginInstance, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM8Module = createModel<CM8Module, CM8ModuleWidget>("CatroModulo_CM-8");
