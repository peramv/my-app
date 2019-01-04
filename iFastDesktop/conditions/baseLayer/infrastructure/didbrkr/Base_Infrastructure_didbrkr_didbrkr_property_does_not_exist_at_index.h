#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_didbrkr_didbrkr_property_does_not_exist_at_index : public CConditionObject
	{
	public:
		CBase_Infrastructure_didbrkr_didbrkr_property_does_not_exist_at_index() { }
		~CBase_Infrastructure_didbrkr_didbrkr_property_does_not_exist_at_index() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_PROPERTY_DOES_NOT_EXIST_AT_INDEX")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Property does not exist at index %index%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Property does not exist at index %index%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Eigenschaft existiert nicht im Index %index%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La propiedad no existe en el índice %index%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La propriété n'existe pas à l'index %index%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eigenschap bestaat niet in index %index%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



