#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_inventory_tracking_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_inventory_tracking_error() { }
		~CIFast_IFast_ifastdbrkr_err_inventory_tracking_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVENTORY_TRACKING_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Inventory Tracking (FIFO) Error.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de suivi d'inventaire (PEPS)")); }

        // Actions
	};
}



