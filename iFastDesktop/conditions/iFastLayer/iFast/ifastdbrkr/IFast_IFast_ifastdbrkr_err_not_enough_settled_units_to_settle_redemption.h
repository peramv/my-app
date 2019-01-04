#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_not_enough_settled_units_to_settle_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_not_enough_settled_units_to_settle_redemption() { }
		~CIFast_IFast_ifastdbrkr_err_not_enough_settled_units_to_settle_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_ENOUGH_SETTLED_UNITS_TO_SETTLE_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not enough settled units to settle the redemption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Unités réglées insuffisantes pour le règlement du rachat")); }

        // Actions
	};
}



