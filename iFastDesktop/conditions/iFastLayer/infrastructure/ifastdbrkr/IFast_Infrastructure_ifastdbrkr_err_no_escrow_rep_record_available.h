#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_no_escrow_rep_record_available : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_no_escrow_rep_record_available() { }
		~CIFast_Infrastructure_ifastdbrkr_err_no_escrow_rep_record_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ESCROW_REP_RECORD_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("NASU social code options not found (B15).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("NASU social code options not found (B15).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("NASU-Sozialcode-Optionen nicht gefunden (B15).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comunicación con el host devolvión un error, RESP_INVALID_PIN_SEC_METHOD. El código de retorno CICS es %CICSError%, el código de retorno WS00221 es %error%, la ubicación de retorno WS00221 es %loc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les options de code social de réglage de nouveau compte sont introuvables (B15).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Communicatie met host heeft fout gegenereerd, RESP_INVALID_PIN_SEC_METHOD. CICS retourcode is %CICSError%, WS00221 retourcode is %error%, WS00221 retourlocatie is %loc%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de ingevoerde gegevens. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



