#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_wrn_no_client_settle_instr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_wrn_no_client_settle_instr() { }
		~CIFast_IFast_ifastbp_bp_wrn_no_client_settle_instr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_WRN_NO_CLIENT_SETTLE_INSTR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No settlement instruction for account")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No settlement instruction for account")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune instruction de règlement pour le compte")); }

        // Actions
	};
}



