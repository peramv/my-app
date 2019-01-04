#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_component_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_component_not_found() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_component_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_COMPONENT_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Component %comp% not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Component %comp% not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Komponente %comp% nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el componente %comp%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Composante %comp% introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Component %comp% is niet gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el archivo de propiedades")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



