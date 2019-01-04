#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_broker_inter_address : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_broker_inter_address() { }
		~CIFast_IFast_ifastcbo_err_no_broker_inter_address() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_BROKER_INTER_ADDRESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no broker address available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("There is no broker address available.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There is no broker address available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune adresse de courtier disponible")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please set up broker address or select another broker.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("please set up broker address or select another broker.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please set up broker address or select another broker.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez régler l'adresse du courtier ou sélectionner un autre courtier.")); }
	};
}



