#include "CatroModulo.hpp"
#include "CM_helpers.hpp"

//Catro-Module CM-9: 1-8-1

struct CM9Module : Module {

	enum ParamIds {
		PARAM_SEL,
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_SEL,
		INPUT_CLK,
		INPUT_RST,
		INPUT_1,
		ENUMS(INPUT_IN, 8), 
		NUM_INPUTS
	};
	enum OutputIds {
		ENUMS(OUTPUT_OUT, 8),
        OUTPUT_1,
		NUM_OUTPUTS
	};

	enum LightIds {
        		NUM_LIGHTS
	};

	enum Modes {
		MODE_SPLIT,
		MODE_JOIN,
		MODE_GATE,
		MODE_PASS,
	};

   //initializations
	//int mode;
    dsp::SchmittTrigger clkTrigger;
	dsp::SchmittTrigger rstTrigger;
	CM_stepper stepper;
	int selector = 0;
	float ledx = 30.9;
	float ledy = 50.0;
	float ins[8];
	float outs[8];
	bool gatemode = 0;
	int opmode = 0;
	
	CM9Module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(CM9Module::PARAM_SEL, 0.0, 7.0, 0.0f, "selector", "", 0.0f, 1.0f, 1.0f);
	}

	void process(const ProcessArgs &args) override;

	void onReset() override{
		opmode = 0;
	}

	json_t *dataToJson() override {

		json_t *rootJ = json_object();
		json_t *opmodeJ = json_array();
		json_array_append_new(opmodeJ, json_integer(opmode));
		json_object_set_new(rootJ, "opmode", opmodeJ);
	
		return rootJ;
	}


	void dataFromJson(json_t *rootJ) override {
		// load opmode
		json_t *opmodeJ = json_object_get(rootJ, "opmode");
		opmode = json_integer_value(json_array_get(opmodeJ, 0));
	}
};

void CM9Module::process(const ProcessArgs &args) {

	gatemode = true;

	//process inputs
	int inputsconnected = 0;
	for (int i = 0; i < 8; i++){
		if (inputs[INPUT_IN + i].isConnected()){
			inputsconnected++;
			ins[i] = inputs[INPUT_IN + i].getVoltage();
		}else{
			ins[i] = 0.0f;
		}
	}
	gatemode = (inputsconnected == 0 && inputs[INPUT_1].isConnected() == false);
	
	//process selector
	float selectorparam = clamp(round((inputs[INPUT_SEL].isConnected()) ? inputs[INPUT_SEL].getVoltage() * 0.1 * params[PARAM_SEL].getValue() : params[PARAM_SEL].getValue()), 0, 7);

	//stepper
	if (inputs[INPUT_CLK].isConnected()){
		if (inputs[INPUT_RST].isConnected()){
			if (rstTrigger.process(inputs[INPUT_RST].getVoltage())){
				stepper.reset();
			}
		}
		if (clkTrigger.process(inputs[INPUT_CLK].getVoltage())){
			selector = stepper.step(selectorparam);
		}
	}else{
		selector = selectorparam;
	}

	//process outputs
	//reset all to 0
	for (int i = 0; i < NUM_OUTPUTS; i++){
			outputs[OUTPUT_OUT + i].setVoltage(0.0f);
		}
	outputs[OUTPUT_1].setVoltage(selector * 1.4285714285714285714285714285714f);

	if (gatemode == true){
		if (inputs[INPUT_CLK].isConnected()){
			outputs[OUTPUT_OUT + selector].setVoltage((inputs[INPUT_CLK].getVoltage() > 0) ? 10.0f : 0.0f);
		}else{
			outputs[OUTPUT_OUT + selector].setVoltage(10.0f);
		}
	}else{
		if (inputs[INPUT_1].isConnected()){
			outputs[OUTPUT_OUT + selector].setVoltage(inputs[INPUT_1].getVoltage());
		}else if (inputsconnected > 0){
			outputs[OUTPUT_OUT + selector].setVoltage(ins[selector]);
		}
		if (inputsconnected > 0){
			outputs[OUTPUT_1].setVoltage(ins[selector]);
		}
	}

	if (opmode > 0){
		if (gatemode == true){
			for (int i = 0; i < 8; i++){
				float tempval = outputs[OUTPUT_OUT + i].getVoltage();
				outputs[OUTPUT_OUT + i].setVoltage(10.0f - tempval);
			}
		}else if (opmode == 1){
			for (int i = 0; i < 8; i++){
				float tempval = outputs[OUTPUT_OUT + i].getVoltage();
				outputs[OUTPUT_OUT + i].setVoltage(0.0f - tempval);
			}
			if (inputsconnected > 0){
				outputs[OUTPUT_1].setVoltage(0.0f - ins[selector]);
			}
		}else if (opmode == 2){

			if (inputsconnected > 0){
				for (int i = 0; i < 8; i++){
					outputs[OUTPUT_OUT + i].setVoltage(0.0f - inputs[INPUT_IN + i].getVoltage());
				}
				outputs[OUTPUT_1].setVoltage(outputs[OUTPUT_OUT + selector].getVoltage());
			}else{
				for (int i = 0; i < 8; i++){
					outputs[OUTPUT_OUT + i].setVoltage(0.0f - inputs[INPUT_1].getVoltage());
				}
			}
			
			outputs[OUTPUT_OUT + selector].setVoltage(0.0f);
		}else if (opmode == 3){
			if (inputsconnected > 0){
				for (int i = 0; i < 8; i++){
					outputs[OUTPUT_OUT + i].setVoltage(inputs[INPUT_IN + i].getVoltage());
				}
				outputs[OUTPUT_1].setVoltage(outputs[OUTPUT_OUT + selector].getVoltage());
			}else{
				for (int i = 0; i < 8; i++){
					outputs[OUTPUT_OUT + i].setVoltage(inputs[INPUT_1].getVoltage());
				}
			}
			outputs[OUTPUT_OUT + selector].setVoltage(0.0f);
		}
	}
	//indicator leds
	ledy = 114.1 + 27.7 * selector;

}

struct CM9ModuleWidget : ModuleWidget {

	CM9ModuleWidget(CM9Module *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-9.svg")));

		//addChild(createWidget<ScrewSilver>(Vec(30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 16, 0)));
		addChild(createWidget<ScrewSilver>(Vec(5, 365)));
		// addChild(createWidget<ScrewSilver>(Vec(box.size.x - 60, 365)));

		//widget items
        addParam(createParam<CM_Knob_big_def_tts>(Vec(7.0 , 20.2), module, CM9Module::PARAM_SEL));

		addInput(createInput<CM_Input_small>(Vec(2.8, 65.9), module, CM9Module::INPUT_SEL));
        addInput(createInput<CM_Input_small>(Vec(50.2 , 30.0), module, CM9Module::INPUT_CLK));
        addInput(createInput<CM_Input_small>(Vec(50.2 , 60.2), module, CM9Module::INPUT_RST));
        

		float a = 5.1;
		float b = 46.4;
		float c[8] = {107.5, 135.2, 163.0, 190.7, 218.5, 246.3, 274.0, 301.8};

		addInput(createInput<CM_Input_def>(Vec(25.7, 77.5), module, CM9Module::INPUT_1));

		for (int i = 0; i < 8; i++){
        addInput(createInput<CM_Input_def>(Vec(a, c[i]), module, CM9Module::INPUT_IN + i));
		}

		for (int i = 0; i < 8; i++){
        addOutput(createOutput<CM_Output_def>(Vec(b , c[i] - 6.1), module, CM9Module::OUTPUT_OUT + i));
		}

        addOutput(createOutput<CM_Output_def>(Vec(25.7 , 326.6), module, CM9Module::OUTPUT_1));

		
		if (module)
		{
			//led selector display
			CM9_LedIndicator *ledindicator = new CM9_LedIndicator();
			ledindicator->posx = &module->ledx;
			ledindicator->posy = &module->ledy;
			addChild(ledindicator);

			//Operating mode selector
			CM_OP *opswitch = new CM_OP(53.7, 333.9f);
			opswitch->opmode = &module->opmode;
			addChild(opswitch);
		}
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per pluginInstance, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM9Module = createModel<CM9Module, CM9ModuleWidget>("CatroModulo_CM-9");
