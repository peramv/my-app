#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_inventory_balance_negative : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_inventory_balance_negative() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_inventory_balance_negative() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_INVENTORY_BALANCE_NEGATIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Inventory balance cannot be negative.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Inventory balance cannot be negative.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde de l'inventaire ne peut être négatif.")); }

        // Actions
	};
}



