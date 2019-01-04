#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_fee_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_fee_does_not_exist() { }
		~CIFast_IFast_ifastcbo_err_fund_fee_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_FEE_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund level fee does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision auf Fondslevel existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comisión a nivel del fondo no existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais au niveau du fonds sont inexistant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten op fondsniveau bestaan niet")); }

        // Actions
	};
}



