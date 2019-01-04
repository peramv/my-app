#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cash_instr_not_allowed_for_reg_acc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cash_instr_not_allowed_for_reg_acc() { }
		~CIFast_IFast_ifastcbo_err_cash_instr_not_allowed_for_reg_acc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cash instructions are not permitted for registered accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions sur les espèces ne sont pas autorisées pour les comptes enregistrés.")); }

        // Actions
	};
}



