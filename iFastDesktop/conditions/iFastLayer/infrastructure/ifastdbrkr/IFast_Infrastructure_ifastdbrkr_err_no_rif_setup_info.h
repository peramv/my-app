#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_no_rif_setup_info : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_no_rif_setup_info() { }
		~CIFast_Infrastructure_ifastdbrkr_err_no_rif_setup_info() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_RIF_SETUP_INFO")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid mutual fund transaction ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid mutual fund transaction ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Offene-Investmentfonds-Transaktions-ID.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Identificación de transacción con fondos mutuos no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de transaction de fonds commun de placement invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig transactie-ID beleggingsfonds")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify data entered. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify data entered. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die eingegebenen Daten. Wenn der Eintrag richtig ist, wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify data entered. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données saisies. Si elles sont exactes, communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de ingevoerde gegevens. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



