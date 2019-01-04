﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_mismatch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_mismatch() { }
		~CIFast_IFast_ifastcbo_err_amount_mismatch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_MISMATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total settlement amount/units is not equal to trade amount/units")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant/les unités de règlement total(es) n'est/ne sont pas égal(es) au montant/unités de la transaction.")); }

        // Actions
	};
}



