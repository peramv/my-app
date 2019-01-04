#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_property_does_not_exist : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_property_does_not_exist() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_property_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_PROPERTY_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Property %prop% does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Property %prop% does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Eigenschaft %prop% existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La propiedad %prop% no existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La propriété %prop% n'existe pas.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eigenschap %prop% bestaat niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el archivo de propiedades")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



