#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_perm_cancel_notional_distrib : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_perm_cancel_notional_distrib() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_perm_cancel_notional_distrib() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_NO_PERM_CANCEL_NOTIONAL_DISTRIB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You do not have permission to cancel Notional Distribution with DSC.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("You do not have permission to cancel Notional Distribution with DSC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous n'êtes pas autorisé à annuler la distribution théorique avec FAR.")); }

        // Actions
	};
}



