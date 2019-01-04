#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unverified_deleted_being_duplicate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unverified_deleted_being_duplicate() { }
		~CIFast_IFast_ifastcbo_err_unverified_deleted_being_duplicate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNVERIFIED_DELETED_BEING_DUPLICATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to delete a distribution option unless an unverified deleted distribution option for the same account-fund-class combination is verified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer une option de distribution à moins qu'une option de distribution supprimée non vérifiée pour la même combinaison de compte, fonds et classe ne soit vérifiée.")); }

        // Actions
	};
}



