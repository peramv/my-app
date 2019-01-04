#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_brokercode_and_srchaltaccount_must_be_provided : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_brokercode_and_srchaltaccount_must_be_provided() { }
		~CIFast_IFast_ifastdbrkr_err_brokercode_and_srchaltaccount_must_be_provided() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKERCODE_AND_SRCHALTACCOUNT_MUST_BE_PROVIDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Search Broker Code and Search Alternate Account must be provided.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SrchBrokerCode und SrchAltAccount müssen verfügbar sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Deben proporcionarse SrchBrokerCode y SrchAltAccount")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs de recherche du code de courtier et de l'autre compte doivent être remplis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("SrchBrokerCode en SrchAltAccount moeten worden ingevoerd")); }

        // Actions
	};
}



