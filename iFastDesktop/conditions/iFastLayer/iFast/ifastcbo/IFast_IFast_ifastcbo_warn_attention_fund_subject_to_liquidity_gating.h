#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_attention_fund_subject_to_liquidity_gating : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_attention_fund_subject_to_liquidity_gating() { }
		~CIFast_IFast_ifastcbo_warn_attention_fund_subject_to_liquidity_gating() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Attention Fund %FUND_CODE% subject to liquidity gating measure.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Attention : Fonds assujetti à la mesure de préservation de liquidité.")); }

        // Actions
	};
}



