#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_not_repeatable : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_not_repeatable() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_not_repeatable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_NOT_REPEATABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Data object %props% is not repeatable.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Data object %props% is not repeatable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenobjekt %props% ist nicht wiederholbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El objeto de datos %props% no puede repetirse.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'objet de données %props% ne peut être répété.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dataobject %props% kan niet worden herhaald")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



