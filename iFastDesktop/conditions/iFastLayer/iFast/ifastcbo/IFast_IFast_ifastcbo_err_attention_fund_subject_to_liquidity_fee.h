﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_attention_fund_subject_to_liquidity_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_attention_fund_subject_to_liquidity_fee() { }
		~CIFast_IFast_ifastcbo_err_attention_fund_subject_to_liquidity_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_SUBJECT_TO_LIQUIDITY_FEE_MEASURE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Attention Fund %FUND_CODE% subject to Liquidity Redemption fee.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Attention, pour ce Fonds, des frais de rachat de liquidité sont possibles.")); }

        // Actions
	};
}



