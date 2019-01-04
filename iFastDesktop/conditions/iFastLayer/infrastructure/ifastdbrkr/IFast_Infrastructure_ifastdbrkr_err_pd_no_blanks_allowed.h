#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_pd_no_blanks_allowed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_pd_no_blanks_allowed() { }
		~CIFast_Infrastructure_ifastdbrkr_err_pd_no_blanks_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_NO_BLANKS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid pre-agreement.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid pre-agreement.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Vorvertrag.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Pre-acuerdo no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Préaccord invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige voorovereenkomst")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Eintrag. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de invoer. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}



