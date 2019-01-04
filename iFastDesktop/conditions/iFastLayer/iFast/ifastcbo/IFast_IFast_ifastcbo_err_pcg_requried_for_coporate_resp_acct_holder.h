#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pcg_requried_for_coporate_resp_acct_holder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pcg_requried_for_coporate_resp_acct_holder() { }
		~CIFast_IFast_ifastcbo_err_pcg_requried_for_coporate_resp_acct_holder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PCG_REQURIED_FOR_COPORATE_RESP_ACCT_HOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PCG Business Number is requried for RESP accountholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire du compte REEE doit posséder un numéro d’entreprise PCG.")); }

        // Actions
	};
}



