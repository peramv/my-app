#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_invalid_redefine : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_invalid_redefine() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_invalid_redefine() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_INVALID_REDEFINE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%oldName% is not a valid redefine for %newName%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%oldName% is not a valid redefine for %newName%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%oldName% ist keine gültige Neudefinition für %newName%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%oldName% no es una redefinición válida para %newName%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%oldName% n'est pas une redéfinition valide pour %newName%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%oldName% is geen geldige nieuwe definitie voor %newName%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el archivo de propiedades.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



