#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_invalid_group : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_invalid_group() { }
		~CIFast_Infrastructure_ifastdbrkr_err_invalid_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Authorization failed for: System %sys%, Management Company %mgmt%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Authorization failed for: System %sys%, Management Company %mgmt%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Autorisierung fehlgeschlagen für: System  %sys%, Management-Unternehmen %mgmt%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falló la autorización para: Sistema %sys%, Compañía administradora %mgmt%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'autorisation pour : le système %sys% et l'entreprise de gestion %mgmt%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Machtiging is mislukt voor: Systeem %sys%, Beheerbedrijf %mgmt%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor en meld dit bericht")); }
	};
}



