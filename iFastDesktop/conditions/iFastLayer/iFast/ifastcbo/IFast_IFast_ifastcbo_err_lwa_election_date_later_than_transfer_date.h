#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_lwa_election_date_later_than_transfer_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_lwa_election_date_later_than_transfer_date() { }
		~CIFast_IFast_ifastcbo_err_lwa_election_date_later_than_transfer_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The LWA Election date is later than the Transfer trade date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de choix du MRV est postérieure à la date de transfert.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Modify election date first.")); }
	};
}



