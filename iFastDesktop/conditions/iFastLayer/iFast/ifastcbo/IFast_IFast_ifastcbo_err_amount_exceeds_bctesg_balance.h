#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_exceeds_bctesg_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_exceeds_bctesg_balance() { }
		~CIFast_IFast_ifastcbo_err_amount_exceeds_bctesg_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_EXCEEDS_BCTESG_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount exceeds BCTESG balance.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant dépasse le solde de la SEEEFCB.")); }


        // Actions
	};
}



