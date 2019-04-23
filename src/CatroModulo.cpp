#include "CatroModulo.hpp"

Plugin *plugin;


void init(Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	// Add all Models defined throughout the plugin
	p->addModel(modelCM1Module);
	p->addModel(modelCM2Module);
	p->addModel(modelCM3Module);
	p->addModel(modelCM4Module);
	p->addModel(modelCM5Module);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
