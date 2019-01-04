#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ams_gap_between_reccords : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ams_gap_between_reccords() { }
		~CIFast_IFast_ifastcbo_warn_ams_gap_between_reccords() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_AMS_GAP_BETWEEN_RECCORDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is a gap between records.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un écart entre les enregistrements.")); }

        // Actions
	};
}



