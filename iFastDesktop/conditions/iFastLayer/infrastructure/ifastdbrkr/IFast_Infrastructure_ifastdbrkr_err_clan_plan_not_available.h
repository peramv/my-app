#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_clan_plan_not_available : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_clan_plan_not_available() { }
		~CIFast_Infrastructure_ifastdbrkr_err_clan_plan_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLAN_PLAN_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No dividend calculation information found (A56).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No dividend calculation information found (A56).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Dividenden-Berechnungsinformationen gefunden (A56).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró información sobre el cálculo de dividendos (A56).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information trouvée sur le calcul des dividendes (A56)")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens dividendberekening zijn niet gevonden (A56)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



