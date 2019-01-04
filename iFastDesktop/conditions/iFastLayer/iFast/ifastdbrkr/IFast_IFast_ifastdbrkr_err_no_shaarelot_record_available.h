#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_shaarelot_record_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_shaarelot_record_available() { }
		~CIFast_IFast_ifastdbrkr_err_no_shaarelot_record_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SHAARELOT_RECORD_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No ShareLot record available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("No ShareLot record available.")); }

        // Actions
	};
}



