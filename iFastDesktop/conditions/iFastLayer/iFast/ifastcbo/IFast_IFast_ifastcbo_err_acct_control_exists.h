#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_control_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_control_exists() { }
		~CIFast_IFast_ifastcbo_err_acct_control_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_CONTROL_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Control record already exists or overlapped with existing")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un enregistrement du contrôle du compte existe déjà ou chevauche l'enregistrement existant.")); }

        // Actions
	};
}



