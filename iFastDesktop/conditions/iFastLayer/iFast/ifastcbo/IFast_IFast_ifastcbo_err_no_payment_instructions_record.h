#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_payment_instructions_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_payment_instructions_record() { }
		~CIFast_IFast_ifastcbo_err_no_payment_instructions_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PAYMENT_INSTRUCTIONS_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("For broker %brokername% and payment for %paymentfordescr% there is no pay instructions record at the %paytoentitydescr% level.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("For broker %brokername% and payment for %paymentfordescr% there is no pay instructions record at the %paytoentitydescr% level.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("For broker %brokername% and payment for %paymentfordescr% there is no pay instructions record at the %paytoentitydescr% level.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucun enregistrement d'instructions de paiement au niveau de %paytoentitydescr% pour le courtier %brokername% et le paiement de %paymentfordescr%.")); }

        // Actions
	};
}



