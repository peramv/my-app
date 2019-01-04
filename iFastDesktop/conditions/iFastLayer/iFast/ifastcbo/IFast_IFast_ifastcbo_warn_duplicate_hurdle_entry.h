#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_duplicate_hurdle_entry : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_duplicate_hurdle_entry() { }
		~CIFast_IFast_ifastcbo_warn_duplicate_hurdle_entry() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DUPLICATE_HURDLE_ENTRY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Hurdle Rate Entry.  (%CODE%, %DATE%).")); }

        // Actions
	};
}



