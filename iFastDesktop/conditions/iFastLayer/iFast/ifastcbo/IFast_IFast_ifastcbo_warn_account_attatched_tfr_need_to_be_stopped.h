﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_account_attatched_tfr_need_to_be_stopped : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_account_attatched_tfr_need_to_be_stopped() { }
		~CIFast_IFast_ifastcbo_warn_account_attatched_tfr_need_to_be_stopped() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trailer Fee Rebate set-up will be expired for this account. Press OK to continue.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Trailer Fee Rebate set-up will be expired for this account. Press OK to continue.")); }

        // Actions
	};
}



