#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_last_address : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_last_address() { }
		~CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_last_address() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_DELETE_LAST_ADDRESS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund options information is unavailable (A58).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund options information is unavailable (A58).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds-Optionen-Information nicht verfügbar (A58).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información de opciones de fondos no está disponible (A58).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information sur les options du fonds introuvable (A58).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens fondsopties zijn niet beschikbaar (A58)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie es später nochmals  oder wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Réessayez plus tard ou communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer het later nog eens of neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



