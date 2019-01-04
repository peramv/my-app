#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_acct_has_stopped_swp_or_redem : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_acct_has_stopped_swp_or_redem() { }
		~CIFast_Infrastructure_ifastcbo_err_acct_has_stopped_swp_or_redem() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_HAS_STOPPED_SWP_OR_REDEM")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Method %METHOD% should never be called.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Method '^' should never be called.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Methode %METHOD% sollte niemals aufgerufen werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El método %METHOD% no debe llamarse nunca.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La méthode %METHOD% ne devrait jamais être appelée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Methode %METHOD% mag nooit worden aangeroepen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den CBO-Code.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code CBO.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de CBO-code")); }
	};
}



