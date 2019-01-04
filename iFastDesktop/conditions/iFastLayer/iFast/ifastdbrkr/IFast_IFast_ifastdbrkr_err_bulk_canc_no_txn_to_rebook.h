#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_bulk_canc_no_txn_to_rebook : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_bulk_canc_no_txn_to_rebook() { }
		~CIFast_IFast_ifastdbrkr_err_bulk_canc_no_txn_to_rebook() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BULK_CANC_NO_TXN_TO_REBOOK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no transaction to rebook for Trade Date, Fund and Class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune transaction à reproduire pour la date, le fonds et la classe de la transaction.")); }

        // Actions
	};
}



