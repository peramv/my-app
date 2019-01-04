#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_direct_depst_bank_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_direct_depst_bank_required() { }
		~CIFast_IFast_ifastcbo_err_direct_depst_bank_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIRECT_DEPST_BANK_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Direct Deposit EFT Bank information for Direct Deposit Trade is required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information bancaire du TEF par dépôt direct pour la transaction de dépôt direct est requise.")); }

        // Actions
	};
}



