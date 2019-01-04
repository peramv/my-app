#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_Invalid_Valuation_Date_For_Fund_Class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_Invalid_Valuation_Date_For_Fund_Class() { }
		~CIFast_IFast_ifastdbrkr_err_Invalid_Valuation_Date_For_Fund_Class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_VALUATION_DATE_FOR_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid valuation date for the fund/class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid valuation date for the fund/class.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid valuation date for the fund/class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date d'évaluation valide pour le fonds/classe.")); }

        // Actions
	};
}