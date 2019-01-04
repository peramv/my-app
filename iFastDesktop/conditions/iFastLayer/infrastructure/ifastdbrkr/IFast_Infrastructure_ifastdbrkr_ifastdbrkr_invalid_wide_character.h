#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_invalid_wide_character : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_invalid_wide_character() { }
		~CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_invalid_wide_character() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_INVALID_WIDE_CHARACTER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this alpha code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this alpha code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diesen Alphacode nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este código alfabético.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce code alphabétique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent deze alfabetische code niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify alpha code and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify alpha code and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Alphacode und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify alpha code and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code alphabétique et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de alfacode en voer deze opnieuw in")); }
	};
}



