#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_calculate_eusd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_calculate_eusd() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_calculate_eusd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_CALCULATE_EUSD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot calculate EUSD.")); }

        // Actions
	};
}



