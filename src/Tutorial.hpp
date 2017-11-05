#include "rack.hpp"


using namespace rack;


extern Plugin *plugin;

struct Poti : SVGKnob {
	Poti() {
		minAngle = -0.83*M_PI;
		maxAngle = 0.83*M_PI;
	}
};

struct KekPoti : Poti {
	KekPoti() {
		box.size = Vec(46, 46);
		setSVG(SVG::load(assetPlugin(plugin, "res/KekPoti.svg")));
	}
}; 

struct LilaPoti : Poti {
	LilaPoti() {
		box.size = Vec(46, 46);
		setSVG(SVG::load(assetPlugin(plugin, "res/LilaPoti.svg")));
	}
}; 

struct CelestePoti : Poti {
	CelestePoti() {
		box.size = Vec(46, 46);
		setSVG(SVG::load(assetPlugin(plugin, "res/CelestePoti.svg")));
	}
}; 

struct PirosPoti : Poti {
	PirosPoti() {
		box.size = Vec(46, 46);
		setSVG(SVG::load(assetPlugin(plugin, "res/PirosPoti.svg")));
	}
}; 

struct SargaPoti : Poti {
	SargaPoti() {
		box.size = Vec(46, 46);
		setSVG(SVG::load(assetPlugin(plugin, "res/SargaPoti.svg")));
	}
}; 

struct ZoldPoti : Poti {
	ZoldPoti() {
		box.size = Vec(46, 46);
		setSVG(SVG::load(assetPlugin(plugin, "res/ZoldPoti.svg")));
	}
}; 

struct Fivestate : SVGSwitch, ToggleSwitch {
	Fivestate() {
		addFrame(SVG::load(assetPlugin(plugin, "res/knob/knob1.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/knob/knob2.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/knob/knob3.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/knob/knob4.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/knob/knob5.svg")));
		sw->wrap();
		box.size = sw->box.size;
	}
};



struct Ycsuszka : SVGSlider {
	Ycsuszka() {
		Vec margin = Vec(4.5, 4.5);
		maxHandlePos = Vec(-1, 0).plus(margin);
		minHandlePos = Vec(-4, 110).plus(margin);
		background->svg = SVG::load(assetPlugin(plugin, "res/xydolgok/yvonal.svg"));
		background->wrap();
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
		handle->svg = SVG::load(assetPlugin(plugin, "res/xydolgok/kozepkor.svg"));
		handle->wrap();
	}
};

struct Xcsuszka : SVGSlider {
	Xcsuszka() {
		Vec margin = Vec(4.5, 4.5);
		maxHandlePos = Vec(110, -4).plus(margin);
		minHandlePos = Vec(2, -4).plus(margin);
		background->svg = SVG::load(assetPlugin(plugin, "res/xydolgok/xvonal.svg"));
		background->wrap();
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
		handle->svg = SVG::load(assetPlugin(plugin, "res/xydolgok/kozepkor.svg"));
		handle->wrap();
	}
};

////////////////////
// module widgets
////////////////////

struct MagasW : ModuleWidget {
	MagasW();
};

struct AlacsonyW : ModuleWidget {
	AlacsonyW();
};