#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_transaction_date_must_be_greater_than_program_start_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_transaction_date_must_be_greater_than_program_start_date() { }
		~CIFast_IFast_ifastcbo_warn_resp_transaction_date_must_be_greater_than_program_start_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_TRANSACTION_DATE_MUST_BE_GREATER_THAN_PROGRAM_START_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction date must be greater than program start date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction doit être ultérieure à la date de début du programme.")); }

        // Actions
	};
}



