#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cmd_after_lcmd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cmd_after_lcmd() { }
		~CIFast_IFast_ifastcbo_err_cmd_after_lcmd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CMD_AFTER_LCMD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Maturity Date is after Legal Contract Maturity Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance du contrat est postérieure à la date d'échéance du contrat légal.")); }

        // Actions
	};
}



