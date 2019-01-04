#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_invalid_redefine : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_invalid_redefine() { }
		~CBase_Ifds_didbrkr_didbrkr_invalid_redefine() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_INVALID_REDEFINE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: Element %ELEMENT% cannot containt elements of class %CLASS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rentenempfänger (05)-Objekttyp kann nur für nicht-registrierte Steuerarten erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: Element %ELEMENT% cannot containt elements of class %CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : l''élément %ELEMENT% ne peut contenir d'éléments de la classe %CLASS%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: Element %ELEMENT% cannot containt elements of class %CLASS%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



