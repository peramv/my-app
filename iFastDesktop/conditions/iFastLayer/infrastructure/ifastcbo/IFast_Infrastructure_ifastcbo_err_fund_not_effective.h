#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_fund_not_effective : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_fund_not_effective() { }
		~CIFast_Infrastructure_ifastcbo_err_fund_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Unknown exception caught.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Probleme interne. Exception inconnue identifiee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Unbekannte Ausnahme ist aufgetreten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. Se detectó una excepción desconocida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Une exception inconnue a été détectée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Er is een onbekende exceptie aangetroffen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



