#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_funds_in_alloc_not_exchangable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_funds_in_alloc_not_exchangable() { }
		~CIFast_IFast_ifastcbo_err_funds_in_alloc_not_exchangable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDS_IN_ALLOC_NOT_EXCHANGABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %TO_FUND%/%TO_CLASS% cannot be exchanged with fund %FROM_FUND%/%FROM_CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %TO_FUND%/%TO_CLASS% ne peut être échangé avec le fonds %FROM_FUND%/%FROM_CLASS%.")); }

        // Actions
	};
}



