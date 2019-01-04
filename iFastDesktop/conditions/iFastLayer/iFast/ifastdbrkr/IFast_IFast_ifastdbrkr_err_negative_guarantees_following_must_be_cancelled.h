#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_negative_guarantees_following_must_be_cancelled : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_negative_guarantees_following_must_be_cancelled() { }
		~CIFast_IFast_ifastdbrkr_err_negative_guarantees_following_must_be_cancelled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEGATIVE_GUARANTEES_FOLLOWING_MUST_BE_CANCELLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Negative Guarantees following must be cancelled (rebook at will).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les garanties négatives suivantes doivent être annulées (replacer à tout moment).")); }

        // Actions
	};
}



