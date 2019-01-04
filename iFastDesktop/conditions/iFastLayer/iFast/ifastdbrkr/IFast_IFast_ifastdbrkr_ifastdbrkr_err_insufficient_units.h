#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_INSUFFICIENT_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient Units.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Insufficient Units.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Unités insuffisantes")); }

        // Actions
	};
}



