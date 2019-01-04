#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_payinstruct_already_exists_for_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_payinstruct_already_exists_for_broker() { }
		~CIFast_IFast_ifastdbrkr_err_payinstruct_already_exists_for_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAYINSTRUCT_ALREADY_EXISTS_FOR_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pay Instruction already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Pay Instruction already exists for Broker.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Pay Instruction already exists for Broker.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de paiement existent déjà.")); }

        // Actions
	};
}



