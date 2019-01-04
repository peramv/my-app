#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_gmwb_payoption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_gmwb_payoption() { }
		~CIFast_IFast_ifastcbo_err_gmwb_payoption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GMWB_PAYOPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only GMWB funds are eligible when a pay option is selected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls les fonds avec GRM sont admissibles lorsqu'une option de paiement est sélectionnée.")); }

        // Actions
	};
}



