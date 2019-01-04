#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_txn_exist_after_closing_decade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_txn_exist_after_closing_decade() { }
		~CIFast_IFast_ifastdbrkr_err_txn_exist_after_closing_decade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TXN_EXIST_AFTER_CLOSING_DECADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transactions exist after the old/new Closing Decade Start Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transactions exist after the old/new Closing Decade Start Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des transactions existent après la date de début de l'ancienne/de la nouvelle décennie de fermeture.")); }

        // Actions
	};
}



