#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_uc_amt_less_than_res_amt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_uc_amt_less_than_res_amt() { }
		~CIFast_IFast_ifastcbo_err_uc_amt_less_than_res_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UC_AMT_LESS_THAN_RES_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unassisted Balance $%UC_AMT% is less than Residual Unassisted $%RES_AMT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L’Unassisted Balance $%UC_AMT% est inférieur au Residual Unassisted $%RES_AMT%.")); }

        // Actions
	};
}



