#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_client_settle_instr_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_client_settle_instr_mandatory() { }
		~CIFast_IFast_ifastbp_bp_err_client_settle_instr_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_CLIENT_SETTLE_INSTR_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client Settlement Instruction is mandatory")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Client Settlement Instruction is mandatory")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de règlement du client sont requises.")); }

        // Actions
	};
}



