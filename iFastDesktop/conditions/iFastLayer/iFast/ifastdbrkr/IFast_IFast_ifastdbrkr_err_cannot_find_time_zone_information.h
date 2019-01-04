#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_find_time_zone_information : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_find_time_zone_information() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_find_time_zone_information() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_FIND_TIME_ZONE_INFORMATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot find time zone information.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver l'information sur le fuseau horaire.")); }

        // Actions
	};
}



