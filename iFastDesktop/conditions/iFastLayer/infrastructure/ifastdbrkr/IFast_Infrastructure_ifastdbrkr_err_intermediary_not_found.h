#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_intermediary_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_intermediary_not_found() { }
		~CIFast_Infrastructure_ifastdbrkr_err_intermediary_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INTERMEDIARY_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid financial institution summary.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid financial institution summary.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Finanzinstitut-Zusammenfassung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Resumen de institución financiera no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le sommaire de l'institution financière est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig overzicht financiële instelling")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify financial institution information and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify financial institution information and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Finanzinstitut-Informationen und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify financial institution information and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'information sur l'institution financière et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de gegevens van de financiële instelling en voer deze opnieuw in")); }
	};
}



