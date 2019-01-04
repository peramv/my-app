#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_user_does_not_have_permission_to_add_epp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_user_does_not_have_permission_to_add_epp() { }
		~CIFast_IFast_ifastcbo_err_user_does_not_have_permission_to_add_epp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DOES_NOT_HAVE_PERMISSION_TO_ADD_EPP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User does not have permission to add an external product provider")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'a pas l'autorisation d'ajouter un fournisseur de produits externe.")); }

        // Actions
	};
}



