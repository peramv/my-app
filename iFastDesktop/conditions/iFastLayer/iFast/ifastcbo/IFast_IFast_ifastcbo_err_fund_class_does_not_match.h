#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_does_not_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_does_not_match() { }
		~CIFast_IFast_ifastcbo_err_fund_class_does_not_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_DOES_NOT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FundCode or ClassCode does not match the aggregated order.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FundCode or ClassCode does not match the aggregated order.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de fonds et le code de classe ne correspondent pas à l'ordre global.")); }

        // Actions
	};
}



