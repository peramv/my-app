#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_hurdle_between_two_reocrds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_hurdle_between_two_reocrds() { }
		~CIFast_IFast_ifastcbo_err_hurdle_between_two_reocrds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HURDLE_BETWEEN_TWO_REOCRDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Hurdle Rate is entered between existing effective dates.")); }

        // Actions
	};
}



