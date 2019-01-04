#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_authorization_denied : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_authorization_denied() { }
		~CIFast_IFast_ifastdbrkr_err_smq_authorization_denied() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_AUTHORIZATION_DENIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This user is not authorized to access this environment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'est pas autorisé à accéder à cet environnement.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please contact System support.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez communiquer avec le soutien informatique.")); }
	};
}



