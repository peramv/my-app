#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_dilution_records_locked : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_dilution_records_locked() { }
		~CIFast_IFast_ifastdbrkr_err_dilution_records_locked() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_RECORDS_LOCKED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dilution Record is locked, try again later.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dilution Record is locked, try again later.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de dilution est verrouillé, réessayez plus tard.")); }

        // Actions
	};
}



