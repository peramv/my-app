#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entire_acct_assigned : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entire_acct_assigned() { }
		~CIFast_IFast_ifastcbo_err_entire_acct_assigned() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTIRE_ACCT_ASSIGNED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entire Account has been assigned.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das gesamte Konto wurde zugewiesen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha cedido toda la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte a été entièrement mis en garantie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige account is toegewezen")); }

        // Actions
	};
}



