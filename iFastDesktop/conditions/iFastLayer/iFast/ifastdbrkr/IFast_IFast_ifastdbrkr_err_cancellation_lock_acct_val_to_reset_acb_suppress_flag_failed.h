#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancellation_lock_acct_val_to_reset_acb_suppress_flag_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancellation_lock_acct_val_to_reset_acb_suppress_flag_failed() { }
		~CIFast_IFast_ifastdbrkr_err_cancellation_lock_acct_val_to_reset_acb_suppress_flag_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCELLATION_LOCK_ACCT_VAL_TO_RESET_ACB_SUPPRESS_FLAG_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot lock account value to reset ACB Suppress Flag.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de verrouiller la valeur du compte pour réinitialiser le signal de suppression du PBR.")); }

        // Actions
	};
}



