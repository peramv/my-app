#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_acct_has_stopped_pac_or_purch : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_acct_has_stopped_pac_or_purch() { }
		~CIFast_Infrastructure_ifastcbo_err_acct_has_stopped_pac_or_purch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_HAS_STOPPED_PAC_OR_PURCH")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("^'")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^'")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("^'")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("^'")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("^'")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("^'")); }

        // Actions
	};
}



