#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_altacct_required_for_puev_investro : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_altacct_required_for_puev_investro() { }
		~CIFast_IFast_ifastcbo_err_altacct_required_for_puev_investro() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALTACCT_REQUIRED_FOR_PUEV_INVESTRO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Alternate account cannot be blank when PUEV or INVESTRO CAPABLE")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Alternate account cannot be blank when PUEV or INVESTRO CAPABLE")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'autre compte est requis s'il supporte PUEV ou Investro.")); }

        // Actions
	};
}



