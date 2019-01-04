#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_expire_date_lessthan_effective_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_expire_date_lessthan_effective_date() { }
		~CIFast_IFast_ifastcbo_err_expire_date_lessthan_effective_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXPIRE_DATE_LESSTHAN_EFFECTIVE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Expire date must be greater than the effective date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Expire date must be greater than the effective date.")); }

        // Actions
	};
}



