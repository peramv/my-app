#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fund_detl_rec_is_locked : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fund_detl_rec_is_locked() { }
		~CIFast_IFast_ifastdbrkr_err_fund_detl_rec_is_locked() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_DETL_REC_IS_LOCKED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund-Detl record is locked.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund-Detl record is locked.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund-Detl record is locked.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des détails du fonds est verrouillé.")); }

        // Actions
	};
}



