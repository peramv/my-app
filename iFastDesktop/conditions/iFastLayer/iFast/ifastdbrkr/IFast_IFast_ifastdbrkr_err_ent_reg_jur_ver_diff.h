#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ent_reg_jur_ver_diff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ent_reg_jur_ver_diff() { }
		~CIFast_IFast_ifastdbrkr_err_ent_reg_jur_ver_diff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENT_REG_JUR_VER_DIFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify Entity Regulatory Jurisdiction record, version numbers are different.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier l'enregistrement du territoire de réglementation de l'entité Les numéros de version sont différents")); }

        // Actions
	};
}



