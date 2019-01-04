#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_redemptions_suspended_liquidity_measure : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_redemptions_suspended_liquidity_measure() { }
		~CIFast_IFast_ifastdbrkr_err_redemptions_suspended_liquidity_measure() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DBRKR_REDEMPTIONS_SUSPENDED_LIQUIDITY_MEASURE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemptions suspended - Liquidity measure.")); }		
		virtual DString GetMessage_FR_CA() const { return DString(I_("Rachats suspendus - mesure de liquidité.")); }

        // Actions
	};
}

