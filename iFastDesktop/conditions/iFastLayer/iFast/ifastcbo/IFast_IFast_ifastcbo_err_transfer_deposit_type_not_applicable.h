#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_deposit_type_not_applicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_deposit_type_not_applicable() { }
		~CIFast_IFast_ifastcbo_err_transfer_deposit_type_not_applicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_DEPOSIT_TYPE_NOT_APPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit Type is not applicable for Transaction Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Deposit Type is not applicable for Transaction Type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de dépôt n'est pas applicable au type de transaction.")); }

        // Actions
	};
}



