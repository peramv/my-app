#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_additional_trade_date_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_additional_trade_date_exist() { }
		~CIFast_IFast_ifastdbrkr_err_no_additional_trade_date_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ADDITIONAL_TRADE_DATE_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No valid trade dates exist for the Fund/Class-Transaction type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune date de transaction valide n'existe pour le fonds/la classe/le type de transaction.")); }

        // Actions
	};
}



