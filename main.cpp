

#define FALSE_LL_LIB
#include "libmod.hpp"
#include "libmodenums.hpp"
#include "ModInfo.hpp"

#if !defined(FALSE_LL_LIB)
#define LOAD_EVENTS
#include "../../../llcpp/util/list/linked/LinkedList.hpp"
#else
#include "falselllib.hpp"
#endif

#include <iostream>

namespace modapi as llcpp::modlibcore::v2;

ll_str_t getStatusID(const modapi::enums::StatusID& id) {
	switch (id) {
		case modapi::enums::StatusID::NOT_INITIALITED:
			return "NOT_INITIALITED";
		case modapi::enums::StatusID::OK:
			return "OK";
		case modapi::enums::StatusID::ERROR_OPENING_MOD:
			return "ERROR_OPENING_MOD";
		case modapi::enums::StatusID::ERROR_GET_MOD_DATA:
			return "ERROR_GET_MOD_DATA";
		case modapi::enums::StatusID::ERROR_MOD_DATA_NULL:
			return "ERROR_MOD_DATA_NULL";
		case modapi::enums::StatusID::ERROR_MOD_NAME_NULL:
			return "ERROR_MOD_NAME_NULL";
		case modapi::enums::StatusID::ERROR_MOD_VERSION_NULL:
			return "ERROR_MOD_VERSION_NULL";
		case modapi::enums::StatusID::ERROR_DEPENDENCES_NO_VALID_CORRELATION_1:
			return "ERROR_DEPENDENCES_NO_VALID_CORRELATION_1";
		case modapi::enums::StatusID::ERROR_DEPENDENCES_NO_VALID_CORRELATION_2:
			return "ERROR_DEPENDENCES_NO_VALID_CORRELATION_2";
		case modapi::enums::StatusID::ERROR_DEPENDENCES_EXTRA_NO_VALID_CORRELATION_1:
			return "ERROR_DEPENDENCES_EXTRA_NO_VALID_CORRELATION_1";
		case modapi::enums::StatusID::ERROR_DEPENDENCES_EXTRA_NO_VALID_CORRELATION_2:
			return "ERROR_DEPENDENCES_EXTRA_NO_VALID_CORRELATION_2";
		default:
			return "null";
	}
}

void printModErrors(modapi::ModInfoEx* mod) {
	printf("Fileanme: %s\n", mod->getFilename());
	printf("\tMod status: %s\n", getStatusID(mod->getStatusID()));
	if (mod->getStatusID() == modapi::enums::StatusID::OK) {
		const modapi::ModData* data = mod->getModData();

		printf("\tModName: %s\n", data->getModName());
		printf("\tModVersion: %s\n", data->getModVersion());

		const modapi::ModBasicData* dep = data->getDependences();
		if (dep) {
			printf("\tPrinting dependences...\n");
			len_t num = data->getNumDependences();
			for (len_t i = 0; i < num; i++)
				printf("\t\t%s:%s\n", dep->getModName(), dep->getModVersion());
		}

		List<const modapi::ModBasicData*>* depNotFound = mod->getDependencesNotFound();
		if (depNotFound->size() > 0) {
			printf("\tDependences not found:\n");
			depNotFound->foreach([](const modapi::ModBasicData* d) {
				printf("\t\t%s:%s\n", d->getModName(), d->getModVersion());
			});
		}
	}
}

int main() {
	modapi::ModLoader modLoader(modapi::enums::OSSystem::WINDOWS);
	ll_int64_t errors = modLoader.load();
	printf("Num error ocurred: %i\n", errors);

	modLoader.getLoadedMods()->foreach(printModErrors);
	modLoader.getErrorMods()->foreach(printModErrors);

	if (modLoader.getErrorMods()->len() > 0) {
		printf("There are dependences not satisfied");
		return -1;
	}

	// Dependencias satisfechas
	/// Extract all mods...
	modapi::ModVector* modVector = modLoader.getModsToUse();
	for (auto i : *modVector)
		delete i;
	delete modVector;

	return 0;
}