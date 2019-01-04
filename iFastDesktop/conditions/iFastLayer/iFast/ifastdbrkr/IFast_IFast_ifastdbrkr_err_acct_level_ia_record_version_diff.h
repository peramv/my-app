#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_version_diff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_version_diff() { }
		~CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_version_diff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_LEVEL_IA_RECORD_VERSION_DIFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify Investor Authorization record, version numbers are different.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier l'enregistrement d'autorisation de l'investisseur, les numéros de versions sont différents.")); }

        // Actions
	};
}



