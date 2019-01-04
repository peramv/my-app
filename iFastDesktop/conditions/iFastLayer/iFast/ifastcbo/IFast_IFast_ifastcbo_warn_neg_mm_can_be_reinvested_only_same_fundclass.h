#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_neg_mm_can_be_reinvested_only_same_fundclass : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_neg_mm_can_be_reinvested_only_same_fundclass() { }
		~CIFast_IFast_ifastcbo_warn_neg_mm_can_be_reinvested_only_same_fundclass() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NEG_MM_CAN_BE_REINVESTED_ONLY_SAME_FUNDCLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Negative MM interest can be reinvested only in the same fund/class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Negative MM interest can be reinvested only in the same fund/class.")); }

        // Actions
	};
}



