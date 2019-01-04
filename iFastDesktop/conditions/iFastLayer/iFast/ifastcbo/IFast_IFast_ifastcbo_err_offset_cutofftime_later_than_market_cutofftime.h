#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_offset_cutofftime_later_than_market_cutofftime : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_offset_cutofftime_later_than_market_cutofftime() { }
		~CIFast_IFast_ifastcbo_err_offset_cutofftime_later_than_market_cutofftime() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Offset cut off time is later than market cut off time")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'heure limite de compensation est postérieure à l'heure limite du marché.")); }

        // Actions
	};
}



