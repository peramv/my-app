#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_one_resp_benef_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_one_resp_benef_allowed() { }
		~CIFast_IFast_ifastcbo_err_one_resp_benef_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONE_RESP_BENEF_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one beneficiary is allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul bénéficiaire autorisé")); }

        // Actions
	};
}



