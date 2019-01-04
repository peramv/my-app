#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_contract_closed_for_new_business : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_contract_closed_for_new_business() { }
		~CIFast_IFast_ifastdbrkr_err_contract_closed_for_new_business() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_CLOSED_FOR_NEW_BUSINESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The contract closed for new business")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fermeture du contrat pour cause de nouvelles affaires")); }

        // Actions
	};
}



