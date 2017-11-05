#include "Tutorial.hpp"


struct Alacsony : Module {
	enum ParamIds {
		PITCH1_PARAM,
		PITCH2_PARAM,
		NUM_PARAMS,
		DENSITY_PARAM
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		X_OUTPUT,
		Y_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	

	Alacsony() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

};


void Alacsony::step() {
	
	int szorzo;
	switch ((int)roundf(params[DENSITY_PARAM].value)) {
		case 0: szorzo = 10; break; //ez a sima 0-10
		case 1: szorzo = 1; break;
		case 2: szorzo = 2; break;
		case 3: szorzo = 10; break;
		default: szorzo = 5; break;
	}

	float pitchX = params[PITCH1_PARAM].value;
	pitchX = (pitchX/3)*szorzo;
	outputs[X_OUTPUT].value = pitchX;
	float pitchY = params[PITCH2_PARAM].value;
	pitchY = (pitchY/3)*szorzo;
	outputs[Y_OUTPUT].value = pitchY;
	
		
}


AlacsonyW::AlacsonyW() {
	Alacsony *module = new Alacsony();
	setModule(module);
	box.size = Vec(12 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/BgAlacsony.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(15, 2)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 2)));
	addChild(createScrew<ScrewSilver>(Vec(65, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));

	addParam(createParam<Xcsuszka>(Vec(25, 90), module, Alacsony::PITCH1_PARAM, -3.0, 3.0, 0.0));
	addParam(createParam<Ycsuszka>(Vec(90, 30), module, Alacsony::PITCH2_PARAM, -3.0, 3.0, 0.0));

	addParam(createParam<Fivestate>(Vec(95, 285), module, Alacsony::DENSITY_PARAM, 0.0, 4.0, 4.0));

	addOutput(createOutput<PJ301MPort>(Vec(35, 195), module, Alacsony::X_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(105, 195), module, Alacsony::Y_OUTPUT));
}
	