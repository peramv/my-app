#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_user_def_mat_greater : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_user_def_mat_greater() { }
		~CIFast_IFast_ifastcbo_err_user_def_mat_greater() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DEF_MAT_GREATER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User-defined maturity date is greater than legal contract maturity date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("User-defined maturity date is greater than legal contract maturity date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance définie par l'utilisateur est postérieure à la date d'échéance du contrat légal.")); }

        // Actions
	};
}



