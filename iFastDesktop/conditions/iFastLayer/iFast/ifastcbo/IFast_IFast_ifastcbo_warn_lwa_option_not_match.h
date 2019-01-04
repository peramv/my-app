#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_lwa_option_not_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_lwa_option_not_match() { }
		~CIFast_IFast_ifastcbo_warn_lwa_option_not_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_LWA_OPTION_NOT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("LWA Option of TO and TI sides do not match.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'option MRV des transferts sortant et entrant ne correspond pas.")); }

        // Actions
	};
}



