#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_already_logged_on : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_already_logged_on() { }
		~CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_already_logged_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ALREADY_LOGGED_ON")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An invalid fund number was entered, or a fund number was not entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("An invalid fund number was entered, or a fund number was not entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine ungültige Fonds-Nummer wurde eingegeben oder keine Fonds-Nummer wurde eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se introdujo un número de fondo no válido o no se introdujo un número de fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un numéro de fonds invalide a été saisi ou un numéro de fonds n'a pas été saisi.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een ongeldig fondsnummer ingevoerd, of er is geen fondsnummer ingevoerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify fund code and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify fund code and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Fondscode und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify fund code and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code de fonds et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de fondscode en voer deze opnieuw in")); }
	};
}



