#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_didbrkr_didbrkr_invalid_property_pointer : public CConditionObject
	{
	public:
		CBase_Infrastructure_didbrkr_didbrkr_invalid_property_pointer() { }
		~CBase_Infrastructure_didbrkr_didbrkr_invalid_property_pointer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_INVALID_PROPERTY_POINTER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid property pointer found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid property pointer found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Eigenschaftenzeiger gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se encontró un puntero de propiedades no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un pointeur de propriété invalide a été trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige pointer voor eigenschap gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



