#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_accountable_should_blank_when_dilution_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_accountable_should_blank_when_dilution_exists() { }
		~CIFast_IFast_ifastdbrkr_err_accountable_should_blank_when_dilution_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNTABLE_SHOULD_BLANK_WHEN_DILUTION_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RVCD and Acc Code should be blank, when Dilution exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RVCD and Acc Code should be blank, when Dilution exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs de code de renversement et de code comptable devraient être vides lorsqu'une dilution existe.")); }

        // Actions
	};
}



