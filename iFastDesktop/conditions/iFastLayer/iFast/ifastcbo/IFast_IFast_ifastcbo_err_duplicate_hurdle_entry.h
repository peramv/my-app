#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_hurdle_entry : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_hurdle_entry() { }
		~CIFast_IFast_ifastcbo_err_duplicate_hurdle_entry() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_HURDLE_ENTRY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Hurdle Rate Entry.  (%CODE%, %DATE%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Saisie en double du taux de rendement minimal.  (%CODE%, %DATE%).")); }

        // Actions
	};
}



