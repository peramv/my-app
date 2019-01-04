#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trans_must_be_verified : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trans_must_be_verified() { }
		~CIFast_IFast_ifastdbrkr_err_trans_must_be_verified() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANS_MUST_BE_VERIFIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction must be Verified.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion muss betätigt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe verificarse la transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction doit être vérifiée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactie moet worden geverifieerd")); }

        // Actions
	};
}



