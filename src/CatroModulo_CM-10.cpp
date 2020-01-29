#include "CatroModulo.hpp"

//Catro-Module CM-10: bitStep

struct CM10Module : Module {

	enum ParamIds {
        ENUMS(PARAM_REC, 2),
        ENUMS(PARAM_PLAY, 2),
		NUM_PARAMS
	};
	enum InputIds {
		ENUMS(INPUT_IN, 2),
		ENUMS(INPUT_STEP, 2),
		ENUMS(INPUT_REC, 2),
		ENUMS(INPUT_PLAY, 2),
		NUM_INPUTS
	};
	enum OutputIds {
        ENUMS(OUTPUT_OUT, 2),
        ENUMS(OUTPUT_STEP, 2),
        ENUMS(OUTPUT_CURRENT, 2),
		NUM_OUTPUTS
	};

	enum LightIds {
        NUM_LIGHTS
	};

   //initializations
	dsp::SchmittTrigger stepTrigger[2];
    dsp::SchmittTrigger recTrigger[2];
    dsp::SchmittTrigger playTrigger[2];
    bool lit[2] = {};
    bool currentin[2] = {};
    bool out[2] = {};
    bool rec[2] = {};
    bool play[2] = {};
    	
	CM10Module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configParam(CM10Module::PARAM_REC, 0.0, 1.0, 0.0f, "capture");
        configParam(CM10Module::PARAM_PLAY, 0.0, 1.0, 0.0f, "override");
        configParam(CM10Module::PARAM_REC + 1, 0.0, 1.0, 0.0f, "capture");
        configParam(CM10Module::PARAM_PLAY + 1, 0.0, 1.0, 0.0f, "override");
	}

	void process(const ProcessArgs &args) override;

};

void CM10Module::process(const ProcessArgs &args) {
    for (int i = 0; i < 2; i++){
        if (stepTrigger[i].process(inputs[INPUT_STEP + i].getVoltage())){
            out[i] = currentin[i];
            if (play[i] == true){
                currentin[i] = rec[i];
                play[i] = false;
            }else{
                currentin[i] = (inputs[INPUT_IN + i].getVoltage() > 0);
            }
            
            lit[i] = currentin[i];
        }
        
        if (recTrigger[i].process((inputs[INPUT_REC + i].getVoltage() || params[PARAM_REC + i].getValue()) * 10.0)){
            rec[i] = currentin[i];
        }

        if (playTrigger[i].process((inputs[INPUT_PLAY + i].getVoltage() || params[PARAM_PLAY + i].getValue()) * 10.0)){
            play[i] = true;
        }

        //set outputs
        outputs[OUTPUT_OUT + i].setVoltage(out[i] * 10.0);
        outputs[OUTPUT_STEP + i].setVoltage((bool)(inputs[INPUT_STEP + i].getVoltage()) * 10.0);
        outputs[OUTPUT_CURRENT + i].setVoltage(currentin[i] * 10.0);
    }	
}

struct CM10ModuleWidget : ModuleWidget {

	CM10ModuleWidget(CM10Module *module) {
		setModule(module);
        //positionings
        float c1 = 3.2;
        float c2 = 33.2;
        float rr[6] = {50.7, 102.2, 163.1, 219.6, 271.1, 331.9}; //update positions

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-10.svg")));

		//addChild(createWidget<ScrewSilver>(Vec(30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 16, 0)));
		addChild(createWidget<ScrewSilver>(Vec(5, 365)));
		// addChild(createWidget<ScrewSilver>(Vec(box.size.x - 60, 365)));

        //Step 1
        addParam(createParam<CM_Button_small_red>(Vec(4.7 , 130.1), module, CM10Module::PARAM_REC));
        addParam(createParam<CM_Button_small_red>(Vec(34.7 , 130.1), module, CM10Module::PARAM_PLAY));
        addInput(createInput<CM_Input_def>(Vec(c1, rr[0]), module, CM10Module::INPUT_IN));
        addInput(createInput<CM_Input_def>(Vec(c1, rr[1]), module, CM10Module::INPUT_STEP));
        addInput(createInput<CM_Input_small>(Vec(c1, rr[2]), module, CM10Module::INPUT_REC));
        addInput(createInput<CM_Input_small>(Vec(c2, rr[2]), module, CM10Module::INPUT_PLAY));

        addOutput(createOutput<CM_Output_def>(Vec(c2 , rr[0]), module, CM10Module::OUTPUT_OUT));
        addOutput(createOutput<CM_Output_def>(Vec(c2 , rr[1]), module, CM10Module::OUTPUT_STEP));
        addOutput(createOutput<CM_Output_def>(Vec(18.2 , 72.6 ), module, CM10Module::OUTPUT_CURRENT));


        //LCD displays
        if (module)
        {
            BigLedIndicator *display1 = new BigLedIndicator();
            display1->box.pos = Vec(5.3, 22.1);
            display1->box.size = Vec(49.6, 19.0);
            display1->lit = &module->lit[0];
            addChild(display1);
        }
        //Step 2
        addParam(createParam<CM_Button_small_red>(Vec(4.7 , 300.4), module, CM10Module::PARAM_REC + 1));
        addParam(createParam<CM_Button_small_red>(Vec(34.7 , 300.4), module, CM10Module::PARAM_PLAY + 1));
        addInput(createInput<CM_Input_def>(Vec(c1, rr[3]), module, CM10Module::INPUT_IN + 1));
        addInput(createInput<CM_Input_def>(Vec(c1, rr[4]), module, CM10Module::INPUT_STEP + 1));
        addInput(createInput<CM_Input_small>(Vec(c1, rr[5]), module, CM10Module::INPUT_REC + 1));
        addInput(createInput<CM_Input_small>(Vec(c2, rr[5]), module, CM10Module::INPUT_PLAY + 1));

        addOutput(createOutput<CM_Output_def>(Vec(c2 , rr[3]), module, CM10Module::OUTPUT_OUT + 1));
        addOutput(createOutput<CM_Output_def>(Vec(c2 , rr[4]), module, CM10Module::OUTPUT_STEP + 1));
        addOutput(createOutput<CM_Output_def>(Vec(18.2 , 241.4 ), module, CM10Module::OUTPUT_CURRENT + 1));

        if (module)
        {
            //LCD displays
            BigLedIndicator *display2 = new BigLedIndicator();
            display2->box.pos = Vec(5.3, 190.9);
            display2->box.size = Vec(49.6, 19.0);
            display2->lit = &module->lit[1];
            addChild(display2);
        }
    }
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per pluginInstance, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM10Module = createModel<CM10Module, CM10ModuleWidget>("CatroModulo_CM-10");
