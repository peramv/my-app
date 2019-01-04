#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_no_resp_beneficiary_selected : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_no_resp_beneficiary_selected() { }
		~CIFast_IFast_ifastcbo_warn_no_resp_beneficiary_selected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NO_RESP_BENEFICIARY_SELECTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No RESP Beneficiary selected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun bénéficiaire REEE sélectionné")); }

        // Actions
	};
}



