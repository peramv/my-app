#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_change_clearinfid_pending : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_change_clearinfid_pending() { }
		~CIFast_IFast_ifastcbo_warn_change_clearinfid_pending() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CHANGE_CLEARINFID_PENDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending trade(s) exists.  When changing the Clearing ID please review the clearing instructions of pending trade(s).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Pending trade(s) exists.  When changing the Clearing ID please review the clearing instructions of pending trade(s).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Pending trade(s) exists.  When changing the Clearing ID please review the clearing instructions of pending trade(s).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction(s) en suspens existante(s). Lors du changement du code de compensation, veuillez réviser les instructions de compensation de la/les transaction(s) en suspens.")); }

        // Actions
	};
}



