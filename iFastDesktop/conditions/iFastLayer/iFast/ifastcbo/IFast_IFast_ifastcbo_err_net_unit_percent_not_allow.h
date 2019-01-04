#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_unit_percent_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_unit_percent_not_allow() { }
		~CIFast_IFast_ifastcbo_err_net_unit_percent_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_UNIT_PERCENT_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net is not allowed for Amount type equal to Unit or Percentage.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Net is not allowed for Amount type equal to Unit or Percentage.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Net is not allowed for Amount type equal to Unit or Percentage.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Net non autorisé pour un type de montant identique à Unité ou à Pourcentage")); }

        // Actions
	};
}



