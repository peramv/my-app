#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_bond_return_cannot_be_greater_than_bond_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_bond_return_cannot_be_greater_than_bond_purchase() { }
		~CIFast_IFast_ifastcbo_err_rdsp_bond_return_cannot_be_greater_than_bond_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_BOND_RETURN_CANNOT_BE_GREATER_THAN_BOND_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bond Return amount cannot be greater than the bond purchase amount.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Bond Return amount cannot be greater than the bond purchase amount.")); }

        // Actions
	};
}



