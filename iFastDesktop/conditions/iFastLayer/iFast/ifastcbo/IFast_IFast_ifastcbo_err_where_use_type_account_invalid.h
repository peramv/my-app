#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_where_use_type_account_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_where_use_type_account_invalid() { }
		~CIFast_IFast_ifastcbo_err_where_use_type_account_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WHERE_USE_TYPE_ACCOUNT_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You can only attach an Account using the Account Entity Maintenance screen.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous ne pouvez saisir un compte qu'en utilisant l'écran de maintenant de l'entité du compte.")); }

        // Actions
	};
}



