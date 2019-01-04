#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_from_fnd_cannot_be_fnd_load_type_for_amt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_from_fnd_cannot_be_fnd_load_type_for_amt() { }
		~CIFast_IFast_ifastcbo_warn_from_fnd_cannot_be_fnd_load_type_for_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From-Fund cannot be fund load type for chosen Amount Type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("From-Fund cannot be fund load type for chosen Amount Type.")); }

        // Actions
	};
}