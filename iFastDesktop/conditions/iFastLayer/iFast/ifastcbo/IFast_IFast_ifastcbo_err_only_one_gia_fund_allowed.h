#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_one_gia_fund_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_one_gia_fund_allowed() { }
		~CIFast_IFast_ifastcbo_err_only_one_gia_fund_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_ONE_GIA_FUND_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one fund with GI fund category is allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul fonds de catégorie FIG est autorisé.")); }

        // Actions
	};
}



