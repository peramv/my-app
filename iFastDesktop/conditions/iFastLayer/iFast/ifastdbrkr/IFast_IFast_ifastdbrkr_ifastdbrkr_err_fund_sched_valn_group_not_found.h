#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_fund_sched_valn_group_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_fund_sched_valn_group_not_found() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_fund_sched_valn_group_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_FUND_SCHED_VALN_GROUP_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Schedule for a non-empty 'VALN' Fund Group not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Schedule for a non-empty 'VALN' Fund Group not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le tableau de fonds pour l'évaluation existante du groupe de fonds est introuvable.")); }

        // Actions
	};
}



