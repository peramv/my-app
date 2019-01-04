#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_instruction_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_instruction_already_exists() { }
		~CIFast_IFast_ifastdbrkr_err_instruction_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSTRUCTION_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Instruction already exist for Red Code/Payment Type/Addr Code/Bank Account")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des instructions existent déjà pour le code rouge, le type de paiement, le code d’adresse et le compte bancaire.")); }

        // Actions
	};
}



