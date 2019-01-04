#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_exists() { }
		~CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_LEVEL_IA_RECORD_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Investor Authorization record already exist or overlap.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un enregistrement d'autorisation de l'investisseur existe déjà ou chevauche celui-ci.")); }

        // Actions
	};
}



