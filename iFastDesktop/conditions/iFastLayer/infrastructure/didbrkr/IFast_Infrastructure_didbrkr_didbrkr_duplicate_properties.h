#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_duplicate_properties : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_duplicate_properties() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_duplicate_properties() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_DUPLICATE_PROPERTIES")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Element %ele% is duplicated in properties file %file%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Element %ele% is duplicated in properties file %file%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Element %ele% ist in der Eigenschaftendatei %file% doppelt vorhanden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El elemento %ele% está repetido en el archivo de propiedades %file%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'élément %ele% est copié dans le fichier des propriétés %file%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Element %ele% is gedupliceerd in eigenschappenbestand %file%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el archivo de propiedades")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



