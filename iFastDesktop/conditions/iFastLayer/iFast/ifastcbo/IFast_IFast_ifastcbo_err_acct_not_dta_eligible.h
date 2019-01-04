#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_not_dta_eligible : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_not_dta_eligible() { }
		~CIFast_IFast_ifastcbo_err_acct_not_dta_eligible() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_NOT_DTA_ELIGIBLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account is not eligible to do direct trading.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("This account is not eligible to do direct trading.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("This account is not eligible to do direct trading.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce compte n'est pas admissible pour une opération directe.")); }

        // Actions
	};
}



