#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_acct_locked_no_redemption_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_acct_locked_no_redemption_available() { }
		~CIFast_IFast_ifastcbo_err_warn_acct_locked_no_redemption_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ACCT_LOCKED_NO_REDEMPTION_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is locked in, no redemption available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto ist festgeschrieben, keine Tilgung möglich")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta está bloqueada, no hay rescate disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte est immobilisé, aucun rachat possible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account is vergrendeld, geen aflossing mogelijk")); }

        // Actions
	};
}



