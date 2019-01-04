#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_country_of_expr_is_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_country_of_expr_is_required() { }
		~CIFast_IFast_ifastcbo_err_country_of_expr_is_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COUNTRY_OF_EXPR_IS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Country of Exposure is required for %RISK_TYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Country of Exposure is required for %RISK_TYPE%.")); }

        // Actions
	};
}