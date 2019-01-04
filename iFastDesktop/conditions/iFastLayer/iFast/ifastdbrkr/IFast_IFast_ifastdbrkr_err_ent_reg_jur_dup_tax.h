#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ent_reg_jur_dup_tax : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ent_reg_jur_dup_tax() { }
		~CIFast_IFast_ifastdbrkr_err_ent_reg_jur_dup_tax() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENT_REG_JUR_DUP_TAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Tax Reporting Jurisdiction is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Doublon du territoire fiscal non autorisé")); }

        // Actions
	};
}



