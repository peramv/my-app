#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_banking_records_for_payment_for : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_banking_records_for_payment_for() { }
		~CIFast_IFast_ifastcbo_err_no_banking_records_for_payment_for() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_BANKING_RECORDS_FOR_PAYMENT_FOR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No banking instructions records set up for payment for: %paymentfor%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement d'instructions bancaires n'est réglé pour le paiement de : %paymentfor%.")); }

        // Actions
	};
}



