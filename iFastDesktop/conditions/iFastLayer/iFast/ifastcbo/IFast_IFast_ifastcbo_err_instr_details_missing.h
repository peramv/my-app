#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_instr_details_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_instr_details_missing() { }
		~CIFast_IFast_ifastcbo_err_instr_details_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSTR_DETAILS_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Instruction must have at least one allocation record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions doivent comprendre au moins un enregistrement de répartition.")); }

        // Actions
	};
}



