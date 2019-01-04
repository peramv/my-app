#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_settlement_instr_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_settlement_instr_code() { }
		~CIFast_IFast_ifastcbo_err_invalid_settlement_instr_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_SETTLEMENT_INSTR_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid value for Settlement Instructions Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid value for Settlement Instructions Code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur de code d'instructions de règlement invalide")); }

        // Actions
	};
}



