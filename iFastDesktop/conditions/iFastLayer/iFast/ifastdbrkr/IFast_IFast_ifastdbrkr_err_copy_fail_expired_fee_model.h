#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_copy_fail_expired_fee_model : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_copy_fail_expired_fee_model() { }
		~CIFast_IFast_ifastdbrkr_err_copy_fail_expired_fee_model() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COPY_FAIL_EXPIRED_FEE_MODEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Copy fail: expired fee model")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copy fail: expired fee model")); }

        // Actions
	};
}