#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clnt_mth_stmt_for_account_belong_nistmt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clnt_mth_stmt_for_account_belong_nistmt() { }
		~CIFast_IFast_ifastcbo_err_clnt_mth_stmt_for_account_belong_nistmt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLNT_MTH_STMT_FOR_ACCOUNT_BELONG_NISTMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client Monthly Statement Category is only for accounts belonging to NI 31-103 Dealer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de relevé mensuel du client n'est que pour les comptes appartenant au courtier NI 31-103.")); }

        // Actions
	};
}



