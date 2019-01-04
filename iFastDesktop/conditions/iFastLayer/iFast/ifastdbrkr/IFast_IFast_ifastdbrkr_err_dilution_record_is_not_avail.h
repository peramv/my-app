#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_dilution_record_is_not_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_dilution_record_is_not_avail() { }
		~CIFast_IFast_ifastdbrkr_err_dilution_record_is_not_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_RECORD_IS_NOT_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dilution record is not available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Dilution record is not available.")); }

        // Actions
	};
}



