#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_enter_a_valid_suppress_code_for_paytype_x_or_blank_for_s : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_enter_a_valid_suppress_code_for_paytype_x_or_blank_for_s() { }
		~CIFast_IFast_ifastdbrkr_err_enter_a_valid_suppress_code_for_paytype_x_or_blank_for_s() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTER_A_VALID_SUPPRESS_CODE_FOR_PAYTYPE_X_OR_BLANK_FOR_S")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Enter a valid suppress code for paytype 'X', \"or leave blank for paytype 'S'.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enter a valid suppress code for paytype 'X', \"or leave blank for paytype 'S'.")); }

        // Actions
	};
}



