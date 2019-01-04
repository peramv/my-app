#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_different_to_from_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_different_to_from_fund_class() { }
		~CIFast_IFast_ifastcbo_err_transfer_different_to_from_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_DIFFERENT_TO_FROM_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid - Transfer must be within the same Fund/Class")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Invalide – le transfert doit s'effectuer dans le même fonds/la même classe.")); }

        // Actions
	};
}



