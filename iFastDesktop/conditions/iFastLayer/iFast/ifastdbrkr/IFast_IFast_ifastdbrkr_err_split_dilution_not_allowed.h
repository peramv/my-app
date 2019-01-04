#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_split_dilution_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_split_dilution_not_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_split_dilution_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPLIT_DILUTION_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Split Dilution not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Split Dilution not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Dilution divisée non autorisée")); }

        // Actions
	};
}



