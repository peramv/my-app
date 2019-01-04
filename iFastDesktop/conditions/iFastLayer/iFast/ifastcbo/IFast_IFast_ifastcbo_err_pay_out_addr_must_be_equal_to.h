#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pay_out_addr_must_be_equal_to : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pay_out_addr_must_be_equal_to() { }
		~CIFast_IFast_ifastcbo_err_pay_out_addr_must_be_equal_to() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAY_OUT_ADDR_MUST_BE_EQUAL_TO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pay out Address code must be equal to %DIVCHQADDR%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pay out Address code must be equal to %DIVCHQADDR%.")); }

        // Actions
	};
}



