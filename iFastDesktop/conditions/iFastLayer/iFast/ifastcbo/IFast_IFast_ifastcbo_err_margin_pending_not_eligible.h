﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_margin_pending_not_eligible : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_margin_pending_not_eligible() { }
		~CIFast_IFast_ifastcbo_err_margin_pending_not_eligible() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MARGIN_PENDING_NOT_ELIGIBLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending trade(s) exist for this account that are not margin eligible.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Pending trade(s) exist for this account that are not margin eligible.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Pending trade(s) exist for this account that are not margin eligible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a une/des transaction(s) en suspens au compte qui n'est/ne sont pas admissible(s) à une marge.")); }

        // Actions
	};
}



