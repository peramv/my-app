#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_add_linked_contract : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_add_linked_contract() { }
		~CIFast_IFast_ifastcbo_err_add_linked_contract() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADD_LINKED_CONTRACT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please Add linked Contract")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez ajouter un contrat associé.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please Add linked Contract")); }
	};
}



