#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_client_non_reg_margin_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_client_non_reg_margin_acct() { }
		~CIFast_IFast_ifastcbo_err_client_non_reg_margin_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLIENT_NON_REG_MARGIN_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Margin category is applicable only for client, non registered accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Margin category is applicable only for client, non registered accounts.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Margin category is applicable only for client, non registered accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de la marge est uniquement applicable pour les comptes clients non enregistrés.")); }

        // Actions
	};
}



