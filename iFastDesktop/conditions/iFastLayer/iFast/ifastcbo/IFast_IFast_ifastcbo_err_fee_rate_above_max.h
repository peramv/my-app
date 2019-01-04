#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_rate_above_max : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_rate_above_max() { }
		~CIFast_IFast_ifastcbo_err_fee_rate_above_max() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_RATE_ABOVE_MAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%name% exceeds maximum value of %max%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%name% exceeds maximum value of %max%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%name% excède la valeur maximale de %max%.")); }

        // Actions
	};
}



