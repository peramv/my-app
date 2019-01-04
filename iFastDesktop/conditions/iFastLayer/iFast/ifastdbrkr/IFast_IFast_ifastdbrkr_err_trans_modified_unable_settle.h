#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trans_modified_unable_settle : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trans_modified_unable_settle() { }
		~CIFast_IFast_ifastdbrkr_err_trans_modified_unable_settle() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANS_MODIFIED_UNABLE_SETTLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction has been modified.  Unable to settle.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion wurde geändert, kann nicht abgerechnet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha modificado la transacción. Imposible liquidarla.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction a été modifiée. Règlement impossible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactie is gewijzigd, kan niet worden betaald")); }

        // Actions
	};
}



