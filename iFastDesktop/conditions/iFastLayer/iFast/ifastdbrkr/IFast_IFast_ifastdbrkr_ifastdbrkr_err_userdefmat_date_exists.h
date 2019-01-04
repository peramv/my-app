#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_date_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_date_exists() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_date_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_USERDEFMAT_DATE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User-defined maturity date already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("User-defined maturity date already exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une date d'échéance définie par l'utilisateur existe déjà.")); }

        // Actions
	};
}



