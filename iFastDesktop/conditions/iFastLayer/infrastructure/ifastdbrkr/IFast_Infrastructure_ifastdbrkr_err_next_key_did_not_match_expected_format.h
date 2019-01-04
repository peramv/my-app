#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_next_key_did_not_match_expected_format : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_next_key_did_not_match_expected_format() { }
		~CIFast_Infrastructure_ifastdbrkr_err_next_key_did_not_match_expected_format() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEXT_KEY_DID_NOT_MATCH_EXPECTED_FORMAT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund level options not found (A58).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund level options not found (A58).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund-Level-Optionen nicht gefunden (A58).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron opciones a nivel del fondo (A58).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Options au niveau du fonds introuvable (A58)")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opties fondsniveau zijn niet gevonden (A58)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



