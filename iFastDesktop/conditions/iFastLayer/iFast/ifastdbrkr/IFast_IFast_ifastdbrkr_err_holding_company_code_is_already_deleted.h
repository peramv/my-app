#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_holding_company_code_is_already_deleted : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_holding_company_code_is_already_deleted() { }
		~CIFast_IFast_ifastdbrkr_err_holding_company_code_is_already_deleted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HOLDING_COMPANY_CODE_IS_ALREADY_DELETED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Holding Company Code is already deleted.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de société de portefeuille déjà supprimé.")); }

        // Actions
	};
}



