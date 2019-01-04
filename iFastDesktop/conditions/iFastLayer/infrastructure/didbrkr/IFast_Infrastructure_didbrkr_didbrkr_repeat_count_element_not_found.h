#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_repeat_count_element_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_repeat_count_element_not_found() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_repeat_count_element_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_REPEAT_COUNT_ELEMENT_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Repeat count element not found for %props%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Repeat count element not found for %props%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wiederholungs-Zählelement nicht gefunden für %props%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró un elemento de recuento de repeticiones para %props%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'élément de dénombrement de répétition est introuvable pour %props%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Herhalingstellingselement is niet gevonden voor %props%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



