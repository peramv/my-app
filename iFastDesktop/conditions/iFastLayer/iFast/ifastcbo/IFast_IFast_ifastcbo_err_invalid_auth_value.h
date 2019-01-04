#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_auth_value : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_auth_value() { }
		~CIFast_IFast_ifastcbo_err_invalid_auth_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AUTH_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Value not valid for this trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur invalide pour cette transaction")); }

        // Actions
	};
}



