#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_wrong_trans_pending : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_wrong_trans_pending() { }
		~CIFast_IFast_ifastdbrkr_err_wrong_trans_pending() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_TRANS_PENDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("TransPending must either be T, P, L, S or D.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("TransPending muss entweder T, P, L, S oder D sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transacción pendiente debe ser T, P, L,  S o D.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les transaction en suspens doivent être T, P, L, S ou D.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("In behandeling zijnde transactie moet  T, P, L, S of D zijn")); }

        // Actions
	};
}



