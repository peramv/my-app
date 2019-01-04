#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_hurdle_calculated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_hurdle_calculated() { }
		~CIFast_IFast_ifastcbo_err_hurdle_calculated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HURDLE_CALCULATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Hurdle Rate will be calculated between %DATE1% to %DATE2%")); }

        // Actions
	};
}



