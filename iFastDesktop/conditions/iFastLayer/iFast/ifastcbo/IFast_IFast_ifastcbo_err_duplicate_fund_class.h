#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_fund_class() { }
		~CIFast_IFast_ifastcbo_err_duplicate_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Fund and Class code.  (%CODE%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Duplicate Fund and Class code.  (%CODE%).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Duplicate Fund and Class code.  (%CODE%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie des codes de fonds et de classe (%CODE%)")); }

        // Actions
	};
}



