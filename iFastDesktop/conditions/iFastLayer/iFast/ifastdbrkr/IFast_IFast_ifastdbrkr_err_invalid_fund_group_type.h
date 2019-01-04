#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_fund_group_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_fund_group_type() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_fund_group_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUND_GROUP_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Fund Group Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Fund Group Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Fonds-Gruppenart.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de grupo de fondos no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de groupe de fonds invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig type goepsfonds")); }

        // Actions
	};
}



