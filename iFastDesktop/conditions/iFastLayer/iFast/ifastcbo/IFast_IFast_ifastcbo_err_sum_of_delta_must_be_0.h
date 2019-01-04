#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sum_of_delta_must_be_0 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sum_of_delta_must_be_0() { }
		~CIFast_IFast_ifastcbo_err_sum_of_delta_must_be_0() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SUM_OF_DELTA_MUST_BE_0")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The sum of the delta values must be zero.")); }
	};
}