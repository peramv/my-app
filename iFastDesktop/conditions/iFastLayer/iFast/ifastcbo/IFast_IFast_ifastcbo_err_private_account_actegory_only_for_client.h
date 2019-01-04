#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_private_account_actegory_only_for_client : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_private_account_actegory_only_for_client() { }
		~CIFast_IFast_ifastcbo_err_private_account_actegory_only_for_client() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Private account category only allowed for client held accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de compte privée n'est autorisée que pour les comptes détenus par des clients.")); }

        // Actions
	};
}



