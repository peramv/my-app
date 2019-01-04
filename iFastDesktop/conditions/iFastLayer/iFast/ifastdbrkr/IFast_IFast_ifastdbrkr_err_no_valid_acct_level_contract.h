#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_valid_acct_level_contract : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_valid_acct_level_contract() { }
		~CIFast_IFast_ifastdbrkr_err_no_valid_acct_level_contract() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_No_Valid_Acct_Level_CONTRACT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No valid Account-level Contract was found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No valid Account-level Contract was found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun contrat valide au niveau du compte n'a été trouvé.")); }

        // Actions
	};
}



