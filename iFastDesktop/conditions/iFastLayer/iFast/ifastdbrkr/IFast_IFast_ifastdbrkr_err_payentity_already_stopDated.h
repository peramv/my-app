#pragma once

#include "ConditionObject.h"
//File added for INC0031322
namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_payentity_already_stopDated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_payentity_already_stopDated() { }
		~CIFast_IFast_ifastdbrkr_err_payentity_already_stopDated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAYENTITY_ALREADY_STOPDATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Pay Entity assocaited to this Payment Instruction is already stop dated.Please create new payment instruction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité de paiement assocaited à cette instruction de paiement est déjà stop.Please créer une nouvelle instruction de paiement.")); }

        // Actions
	};
}



