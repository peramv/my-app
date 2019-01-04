#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trans_clearing_settle_rec_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trans_clearing_settle_rec_exists() { }
		~CIFast_IFast_ifastdbrkr_err_trans_clearing_settle_rec_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANS_CLEARING_SETTLE_REC_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction clearing settlement record already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaction clearing settlement record already exists.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transaction clearing settlement record already exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement du règlement de compensation de la transaction existe déjà.")); }

        // Actions
	};
}



