#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ent_reg_jur_not_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ent_reg_jur_not_avail() { }
		~CIFast_IFast_ifastdbrkr_err_ent_reg_jur_not_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENT_REG_JUR_NOT_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity Regulatory Jurisdiction record is not available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement concernant les détails du territoire de l'entité n'est pas valable.")); }

        // Actions
	};
}



