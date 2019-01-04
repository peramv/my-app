#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_greater_than_legal : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_greater_than_legal() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_greater_than_legal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_USERDEFMAT_GREATER_THAN_LEGAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User-defined maturity date greater than legal contract maturity date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("User-defined maturity date greater than legal contract maturity date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance définie par l'utilisateur est postérieure à la date d'échéance du contrat légal.")); }

        // Actions
	};
}



