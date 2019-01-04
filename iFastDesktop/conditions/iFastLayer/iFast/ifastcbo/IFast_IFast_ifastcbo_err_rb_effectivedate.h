#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rb_effectivedate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rb_effectivedate() { }
		~CIFast_IFast_ifastcbo_err_rb_effectivedate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RB_EFFECTIVEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot modify effective date on an AMS Rebalancing allocation type")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier la date d'entrée en vigueur du type de répartition de rebalancement de service de gestion de portefeuille.")); }

        // Actions
	};
}



