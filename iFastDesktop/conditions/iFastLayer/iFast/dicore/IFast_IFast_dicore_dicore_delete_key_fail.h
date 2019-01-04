#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_delete_key_fail : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_delete_key_fail() { }
		~CIFast_IFast_dicore_dicore_delete_key_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DELETE_KEY_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify Entity, version numbers are different.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de modifier l'entite, les numeros de version sont differents")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt-Eintrag konnte nicht geändert werden, die Versionsnummer sind verschieden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible modificar la entidad, los números de versión son diferentes")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier l'entité, les numéros de version sont différents.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid kon niet worden gewijzigd, de versienummers zijn verschillend")); }

        // Actions
	};
}



