#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clnt_mth_stmt_for_client_held_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clnt_mth_stmt_for_client_held_account() { }
		~CIFast_IFast_ifastcbo_err_clnt_mth_stmt_for_client_held_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLNT_MTH_STMT_FOR_CLIENT_HELD_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client Monthly Statement Category is only for Client held account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de relevé mensuel du client n'est que pour les comptes détenus par des clients.")); }

        // Actions
	};
}



