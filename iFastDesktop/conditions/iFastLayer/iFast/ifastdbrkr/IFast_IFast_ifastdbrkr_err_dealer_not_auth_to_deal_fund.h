#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_dealer_not_auth_to_deal_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_dealer_not_auth_to_deal_fund() { }
		~CIFast_IFast_ifastdbrkr_err_dealer_not_auth_to_deal_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEALER_NOT_AUTH_TO_DEAL_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dealer Not Authorized to Deal a Fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Händler sind nicht autorisiert, mit einem Fonds zu handeln.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Agente no autorizado a distribuir un fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Courtier non autorisé à traiter un fonds")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handelaar is niet gemachtigd om een fonds te verhandelen")); }

        // Actions
	};
}



