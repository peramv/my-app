#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_please_send_again_as_last_record_was_deleted : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_please_send_again_as_last_record_was_deleted() { }
		~CIFast_Infrastructure_ifastdbrkr_err_please_send_again_as_last_record_was_deleted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PLEASE_SEND_AGAIN_AS_LAST_RECORD_WAS_DELETED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Financial institution information not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Financial institution information not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Finanzinstitut-Information nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró información sobre la institución financiera.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information sur l'institution financière introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens financiële instelling zijn niet gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify financial institution information. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify financial institution information. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Finanzinstitut-Informationen. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify financial institution information. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'information sur l'institution financière. Si la saisie est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de gegevens van de financiële instelling. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}



