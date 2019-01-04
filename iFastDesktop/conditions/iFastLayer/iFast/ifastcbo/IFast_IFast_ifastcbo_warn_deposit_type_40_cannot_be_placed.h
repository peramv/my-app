#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_deposit_type_40_cannot_be_placed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_deposit_type_40_cannot_be_placed() { }
		~CIFast_IFast_ifastcbo_warn_deposit_type_40_cannot_be_placed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DEPOSIT_TYPE_40_CANNOT_BE_PLACED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction with Deposit code 40 cannot be placed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction dont le code de dépôt est 40 ne peut être placée.")); }

        // Actions
	};
}



