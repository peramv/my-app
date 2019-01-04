#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_code_used_by_fundsponsor_cannot_delete : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_code_used_by_fundsponsor_cannot_delete() { }
		~CIFast_IFast_ifastdbrkr_err_code_used_by_fundsponsor_cannot_delete() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CODE_USED_BY_FUNDSPONSOR_CANNOT_DELETE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Code used by FundSponsor, cannot delete.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code utilisé par FundSponsor, suppression impossible.")); }

        // Actions
	};
}



