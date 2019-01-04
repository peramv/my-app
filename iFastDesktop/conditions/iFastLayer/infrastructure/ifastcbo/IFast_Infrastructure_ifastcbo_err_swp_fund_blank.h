#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_swp_fund_blank : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_swp_fund_blank() { }
		~CIFast_Infrastructure_ifastcbo_err_swp_fund_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SWP_FUND_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Object %OBJECT% marked as private use.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Object '^' marked as private use.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Objekt %OBJECT% als Privatnutzung gekennzeichnet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. El objeto %OBJECT% está marcado como de uso privado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. L'objet %OBJECT% est marqué pour une utilisation privée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Object %OBJECT% is aangemerkt voor privé-gebruik")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



