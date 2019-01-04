#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dilution_alloc_same_resp_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dilution_alloc_same_resp_date() { }
		~CIFast_IFast_ifastcbo_err_dilution_alloc_same_resp_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_ALLOC_SAME_RESP_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Same Responsibility Date cannot be assigned to more than one accountable party.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La même date responsabilité ne peut être attribuée à plus d'une partie comptable.")); }

        // Actions
	};
}



