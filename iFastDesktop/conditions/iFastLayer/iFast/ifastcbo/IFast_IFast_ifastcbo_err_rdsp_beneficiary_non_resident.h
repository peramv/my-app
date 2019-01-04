#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_beneficiary_non_resident : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_beneficiary_non_resident() { }
		~CIFast_IFast_ifastcbo_err_rdsp_beneficiary_non_resident() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_BENEFICIARY_NON_RESIDENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary must be a Canadian resident.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Beneficiary must be a Canadian resident.")); }		

        // Actions
	};
}



