#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_txn_cannot_exist_after_decade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_txn_cannot_exist_after_decade() { }
		~CIFast_IFast_ifastdbrkr_err_txn_cannot_exist_after_decade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TXN_CANNOT_EXIST_AFTER_DECADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction cannot exist after closing decade start date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaction cannot exist after closing decade start date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction ne peut exister après la date de début de la décennie de fermeture.")); }

        // Actions
	};
}



