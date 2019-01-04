#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_rep_proposed_date_must_be_future_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_rep_proposed_date_must_be_future_date() { }
		~CIFast_IFast_ifastcbo_err_ams_rep_proposed_date_must_be_future_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_REP_PROPOSED_DATE_MUST_BE_FUTURE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Proposed Live Run Date must be later or equal to Trade Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Proposed Live Run Date must be later or equal to Trade Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date mise à jour courante prévue doit être postérieure ou identique à la date de transaction.")); }

        // Actions
	};
}



