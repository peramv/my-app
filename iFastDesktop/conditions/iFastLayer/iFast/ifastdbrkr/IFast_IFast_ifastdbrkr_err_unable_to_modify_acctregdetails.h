#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_modify_acctregdetails : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_modify_acctregdetails() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_modify_acctregdetails() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_MODIFY_ACCTREGDETAILS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify AcctRegDetails record, version numbers are different.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier l’enregistrement AcctRegDetails, les numéros de versions sont différents.")); }

        // Actions
	};
}



