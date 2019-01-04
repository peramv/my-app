#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_resp_contractids : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_resp_contractids() { }
		~CIFast_IFast_ifastcbo_err_invalid_resp_contractids() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_RESP_CONTRACTIDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Id(s) cannot be empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le(s) code(s) de contrat sont requis.")); }

        // Actions
	};
}



