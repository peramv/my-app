#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_linked_contract_different : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_linked_contract_different() { }
		~CIFast_IFast_ifastcbo_err_linked_contract_different() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LINKED_CONTRACT_DIFFERENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The values chosen for the fields are different from the linked Contract.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les valeurs choisies pour les champs sont différentes que celles du contrat associé.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please correct.")); }
	};
}



