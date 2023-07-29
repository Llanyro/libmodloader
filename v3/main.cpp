/*
 * Main.cpp
 *
 *  Created on: Feb 22, 2023
 *      Author: llanyro
 */
#include "ModLoader.hpp"
// Libs
#include "libs/libmodenums.hpp"
// Objects
#include "objects/ModInfoExtra.hpp"
#include "objects/ModCore.hpp"
#include "objects/ModData.hpp"

// Testing
#include "test/IInterface.hpp"

// System
#include <iostream>

namespace modlib = llcpp::modlibcore;

const char* getStatusID(const modlib::enums::StatusID& id) {
	switch (id) {
		case modlib::enums::StatusID::NOT_INITIALITED:
			return "NOT_INITIALITED";
		case modlib::enums::StatusID::OK:
			return "OK";
		case modlib::enums::StatusID::ERROR_OPENING_MOD:
			return "ERROR_OPENING_MOD";
		case modlib::enums::StatusID::ERROR_GET_MOD_CORE:
			return "ERROR_GET_MOD_CORE";
		case modlib::enums::StatusID::ERROR_MOD_DATA_NULL:
			return "ERROR_MOD_DATA_NULL";
		case modlib::enums::StatusID::ERROR_MOD_NAME_NULL:
			return "ERROR_MOD_NAME_NULL";
		case modlib::enums::StatusID::ERROR_MOD_VERSION_NULL:
			return "ERROR_MOD_VERSION_NULL";
		default:
			return "default";
	}
}

void printModErrors(modlib::ModInfoExtra* mod) {
	printf("Fileanme: %s\n", mod->getFilename());
	printf("\tMod status: %s\n", getStatusID(mod->getStatusID()));
	if (mod->getStatusID() == modlib::enums::StatusID::OK) {

		const modlib::ModData* data = mod->getModCore()->getModData();

		printf("\tModName: %s\n", data->getModName());
		printf("\tModVersion: %s\n", data->getModVersion());

		const modlib::vector::Vector<modlib::ModBasicData*>*
			data_arr = data->getDependences();
		if (data_arr) {
			printf("\tPrinting dependences...\n");
			for (len_t i = 0; i < data_arr->size(); i++)
				printf("\t\t%s:%s\n", 
					(*data_arr->cget(i))->getModName(), 
					(*data_arr->cget(i))->getModVersion());
		}

		List<const modlib::ModBasicData*>* depNotFound = mod->getDependencesNotFound();
		if (depNotFound->size() > 0) {
			printf("\tDependences not found:\n");
			depNotFound->foreach([](const modlib::ModBasicData* d) {
				printf("\t\t%s:%s\n", d->getModName(), d->getModVersion());
			});
		}
	}
}

/*
	Modlib should use Singleton pointer controller to keep external pointers to mod objects
		to the correct value.
	If mod is unloaded, all external objects (from mod) that points to mod object, should point
		to nullptr. So Singleton pointer controller should be the solution.

	+ Add unloadMod()
		A mod can be unloaded if dependant mods are unloaded
	+ Add loadMod()
		A mod can be loaded if its dependences are loaded
	+ Add reloadMod()
		A mod can be reload if modloader load error is 0
	+ Add clearMods()
		Clears mod loader


	Test:
		+ Add mod reqirement function to let mods get back dependences (ModCore*)

	Completed:
		+ Add ModCore
		+ Add ModObject

*/

typedef modlib::test::IInterface* (*GetInterface)();
typedef void (*__init__)(void);

template<class T, class Smtin>
void executeFunc(const modlib::ModInfo* info, const char* functionName, Smtin lamb) {
	T func =
		(T)info->getFunction(functionName);
	if (func)
		lamb(func);
	else {
		const modlib::ModData* data = info->getModCore()->getModData();
		printf("*** Mod: %s::%s does not have '%s' ***\n", 
			data->getModName(), 
			data->getModVersion(), 
			functionName);
	}
}

int main() {
	modlib::ModLoader modLoader(modlib::enums::OSSystem::WINDOWS);
	ll_int64_t errors = modLoader.load();
	fprintf(stderr, "Num error ocurred: %i\n", errors);

	modLoader.getLoadedMods()->foreach(printModErrors);
	modLoader.getErrorMods()->foreach(printModErrors);

	if (modLoader.getErrorMods()->len() > 0) {
		fprintf(stderr, "There are dependences not satisfied\n");
		return -1;
	}

	putchar('\n');

	// Dependencias satisfechas
	/// Extract all mods...
	modlib::ModVector* modVector = modLoader.getModsToUse();

	auto lambda_interface = [](GetInterface in) {
		modlib::test::IInterface* iface = in();

		printf("Initial value: %i\n", iface->get());

		iface->add(17);
		printf("Sum 17: %i\n", iface->get());

		iface->sub(3);
		printf("Sub 3: %i\n", iface->get());

		iface->printText();
	};

	// Execute getInterface in all mods and execute some functions
	for (auto i : *modVector)
		executeFunc<GetInterface>(i, "getInterface", lambda_interface);

	// Execute __init__ in all mods
	for (auto i : *modVector)
		executeFunc<__init__>(i, "__init__", [](__init__ in) { in(); });

	// Execute getInterface in all mods and execute some functions
	for (auto i : *modVector)
		executeFunc<GetInterface>(i, "getInterface", lambda_interface);

	//for (auto i : *modVector)
	//	delete i;
	delete modVector;

	return 0;
}