#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_exist_for_tax_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_exist_for_tax_year() { }
		~CIFast_IFast_ifastcbo_err_trade_exist_for_tax_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_EXIST_FOR_TAX_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade exist for Tax Year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction existante pour l'année d'imposition")); }

        // Actions
	};
}



