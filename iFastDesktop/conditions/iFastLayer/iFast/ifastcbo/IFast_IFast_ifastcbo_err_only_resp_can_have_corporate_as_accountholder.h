#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_resp_can_have_corporate_as_accountholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_resp_can_have_corporate_as_accountholder() { }
		~CIFast_IFast_ifastcbo_err_only_resp_can_have_corporate_as_accountholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_RESP_CAN_HAVE_CORPORATE_AS_ACCOUNTHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only RESP taxtype can have corporate as accountholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seul le type d’impôt REEE peut avoir une entreprise titulaire du compte.")); }

        // Actions
	};
}



