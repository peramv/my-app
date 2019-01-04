#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_pcg_for_resp_accountholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_pcg_for_resp_accountholder() { }
		~CIFast_IFast_ifastcbo_err_invalid_pcg_for_resp_accountholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PCG_FOR_RESP_ACCOUNTHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid PCG business number for RESP accountholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro d’entreprise PCG invalide pour le titulaire du compte REEE.")); }

        // Actions
	};
}



