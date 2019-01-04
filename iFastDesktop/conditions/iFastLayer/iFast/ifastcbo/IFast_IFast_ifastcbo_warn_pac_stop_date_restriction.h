#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pac_stop_date_restriction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pac_stop_date_restriction() { }
		~CIFast_IFast_ifastcbo_warn_pac_stop_date_restriction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PAC_STOP_DATE_RESTRICTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New Stop Date should be between Current Buisness Day %DATE1% and Current PAC Stop Date %DATE2% .")); }

        // Actions
	};
}



