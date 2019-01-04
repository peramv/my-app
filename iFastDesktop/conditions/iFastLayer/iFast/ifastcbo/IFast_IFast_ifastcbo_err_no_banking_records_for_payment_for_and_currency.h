#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_banking_records_for_payment_for_and_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_banking_records_for_payment_for_and_currency() { }
		~CIFast_IFast_ifastcbo_err_no_banking_records_for_payment_for_and_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_BANKING_RECORDS_FOR_PAYMENT_FOR_AND_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No banking instructions records set up for payment for :%paymentfor% and currency: %currency%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("For the current values of payment for (%paymentfor%) and currency (%currency%) there are no banking instructions records set up.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("For the current values of payment for (%paymentfor%) and currency (%currency%) there are no banking instructions records set up.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement d'instructions bancaires n'est réglé pour le paiement de : %paymentfor%, dans la monnaie suivante : %currency%.")); }

        // Actions
	};
}



