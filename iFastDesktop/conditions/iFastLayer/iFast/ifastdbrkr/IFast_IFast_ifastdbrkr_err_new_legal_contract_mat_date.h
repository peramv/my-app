#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_new_legal_contract_mat_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_new_legal_contract_mat_date() { }
		~CIFast_IFast_ifastdbrkr_err_new_legal_contract_mat_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEW_LEGAL_CONTRACT_MAT_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New Legal Contract Maturity date cannot be less than Contract Maturity Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("New Legal Contract Maturity date cannot be less than Contract Maturity Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La nouvelle date d'échéance du contrat légal ne peut être antérieure à la date d'échéance du contrat.")); }

        // Actions
	};
}



