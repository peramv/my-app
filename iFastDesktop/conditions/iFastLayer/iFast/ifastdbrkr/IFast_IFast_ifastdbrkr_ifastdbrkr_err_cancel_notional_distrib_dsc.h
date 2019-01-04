#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_cancel_notional_distrib_dsc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_cancel_notional_distrib_dsc() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_cancel_notional_distrib_dsc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_CANCEL_NOTIONAL_DISTRIB_DSC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You are cancelling Notional Distribution with DSC.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("You are cancelling Notional Distribution with DSC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous êtes en train d'annuler la distribution théorique avec FAR.")); }

        // Actions
	};
}



