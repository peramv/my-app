#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amt_type_notapplicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amt_type_notapplicable() { }
		~CIFast_IFast_ifastcbo_err_amt_type_notapplicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_TYPE_NOTAPPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value is not applicable for this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur non applicable pour ce compte")); }

        // Actions
	};
}



