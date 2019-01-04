#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_different_siblingonly_status : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_different_siblingonly_status() { }
		~CIFast_IFast_ifastcbo_err_different_siblingonly_status() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIFFERENT_SIBLINGONLY_STATUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accounts have different SiblingOnly status - Ensure transfer meets regulations.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les comptes ont des statuts Frère/sœur seulement différents — assurez-vous que le transfert respecte les réglementations.")); }

        // Actions
	};
}



