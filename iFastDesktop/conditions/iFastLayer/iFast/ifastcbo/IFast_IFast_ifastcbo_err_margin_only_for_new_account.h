#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_margin_only_for_new_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_margin_only_for_new_account() { }
		~CIFast_IFast_ifastcbo_err_margin_only_for_new_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MARGIN_ONLY_FOR_NEW_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Margin category can only be setup for new accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Margin category can only be setup for new accounts.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Margin category can only be setup for new accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de la marge ne peut être réglée que pour les nouveaux comptes.")); }

        // Actions
	};
}



