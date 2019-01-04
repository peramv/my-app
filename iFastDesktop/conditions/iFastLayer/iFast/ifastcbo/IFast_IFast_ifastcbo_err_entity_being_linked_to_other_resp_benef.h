#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_being_linked_to_other_resp_benef : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_being_linked_to_other_resp_benef() { }
		~CIFast_IFast_ifastcbo_err_entity_being_linked_to_other_resp_benef() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_BEING_LINKED_TO_OTHER_RESP_BENEF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity is being linked with other RESP Beneficiary.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité est en cours d'association avec un autre bénéficiaire REEE.")); }

        // Actions
	};
}



