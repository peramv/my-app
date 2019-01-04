#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_missing_default_settlement_instr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_missing_default_settlement_instr() { }
		~CIFast_IFast_ifastcbo_err_missing_default_settlement_instr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISSING_DEFAULT_SETTLEMENT_INSTR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no active default settlement instruction for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Missing default settlement instruction")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucune instruction de règlement par défaut active pour ce compte.")); }

        // Actions
	};
}



