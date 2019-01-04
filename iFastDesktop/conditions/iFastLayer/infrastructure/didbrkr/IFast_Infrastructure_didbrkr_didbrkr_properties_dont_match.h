#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_properties_dont_match : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_properties_dont_match() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_properties_dont_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_PROPERTIES_DONT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The properties of DataElement %ele1% do not match the properties of DataElement %ele2%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The properties of DataElement %ele1% do not match the properties of DataElement %ele2%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Eigenschaften von Datenelement %ele1% passen nicht zu den Eigenschaften von Datenelement %ele2%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las propiedades del elemento de datos %ele1% no coinciden con las propiedades del elemento de datos %ele2%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les propriétés de l'élément de données %ele1% ne correspondent pas à celles de l'élément de données %ele2%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De eigenschappen van DataElement %ele1% komen niet overeen met de eigenschappen van DataElement %ele2%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file(s)")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file(s)")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei(en)")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check properties file(s)")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le ou les fichiers des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand of de bestanden met eigenschappen")); }
	};
}



