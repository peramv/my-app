#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_direct_depst_bank_for_can_bank_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_direct_depst_bank_for_can_bank_only() { }
		~CIFast_IFast_ifastcbo_err_direct_depst_bank_for_can_bank_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Direct Deposit EFT Banking is applied only to Canadian Bank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information bancaire du TEF par dépôt direct n'est applicable qu'aux banques canadiennes.")); }

        // Actions
	};
}



