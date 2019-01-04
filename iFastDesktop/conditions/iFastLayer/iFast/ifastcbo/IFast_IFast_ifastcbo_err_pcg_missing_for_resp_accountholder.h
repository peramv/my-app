#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pcg_missing_for_resp_accountholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pcg_missing_for_resp_accountholder() { }
		~CIFast_IFast_ifastcbo_err_pcg_missing_for_resp_accountholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PCG_MISSING_FOR_RESP_ACCOUNTHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PCG business number is missing for RESP accountholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d’entreprise PCG est manquant pour le titulaire du compte REEE.")); }

        // Actions
	};
}



