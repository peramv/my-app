#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_purchase_invalid_deposit_type_for_alloc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_purchase_invalid_deposit_type_for_alloc() { }
		~CIFast_IFast_ifastcbo_err_purchase_invalid_deposit_type_for_alloc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PURCHASE_INVALID_DEPOSIT_TYPE_FOR_ALLOC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Deposit Type for allocated Trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid Deposit Type for allocated Trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de dépôt invalide pour la transaction répartie.")); }

        // Actions
	};
}



