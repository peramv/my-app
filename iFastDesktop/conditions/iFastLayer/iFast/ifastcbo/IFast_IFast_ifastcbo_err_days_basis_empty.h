#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_days_basis_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_days_basis_empty() { }
		~CIFast_IFast_ifastcbo_err_days_basis_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DAYS_BASIS_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Days Basis cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de la base des jours ne peut être vide.")); }

        // Actions
	};
}



