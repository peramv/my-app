#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ent_reg_dup_id_reg : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ent_reg_dup_id_reg() { }
		~CIFast_IFast_ifastdbrkr_err_ent_reg_dup_id_reg() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENT_REG_DUP_ID_REG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Entity ID/Regulation is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Doublon code/règlement de l'entité non autorisé.")); }

        // Actions
	};
}



