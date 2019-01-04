#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_user_def_mat_less : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_user_def_mat_less() { }
		~CIFast_IFast_ifastcbo_err_user_def_mat_less() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DEF_MAT_LESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User-defined maturity date is less than %TERM% years from account effective date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance définie par l'utilisateur est antérieure de %TERM% ans à la date d'entrée en vigueur du compte.")); }

        // Actions
	};
}



