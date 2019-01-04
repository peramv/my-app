#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_already_logged_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_already_logged_on() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_already_logged_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ALREADY_LOGGED_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User is already logged on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("User is already logged on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Benutzer ist bereits angemeldet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario ya está conectado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur est déjà connecté.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruiker is al aangemeld")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("No corrective action needed.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("No corrective action needed.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Keine korrigierende Maßnahme erforderlich.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("No corrective action needed.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Aucune correction requise")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Er is geen corrigerende actie nodig")); }
	};
}



