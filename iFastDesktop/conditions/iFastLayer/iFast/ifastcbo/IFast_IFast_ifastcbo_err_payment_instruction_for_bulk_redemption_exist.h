#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_payment_instruction_for_bulk_redemption_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_payment_instruction_for_bulk_redemption_exist() { }
		~CIFast_IFast_ifastcbo_err_payment_instruction_for_bulk_redemption_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAYMENT_INSTRUCTION_FOR_BULK_REDEMPTION_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Payment Instruction for Bulk Redemptions exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de paiement pour les rachats globaux existent.")); }

        // Actions
	};
}



