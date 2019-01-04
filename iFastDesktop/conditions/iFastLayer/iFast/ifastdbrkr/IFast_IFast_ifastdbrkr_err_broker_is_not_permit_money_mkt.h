#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_broker_is_not_permit_money_mkt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_broker_is_not_permit_money_mkt() { }
		~CIFast_IFast_ifastdbrkr_err_broker_is_not_permit_money_mkt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_IS_NOT_PERMIT_MONEY_MKT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker is not permitted to enter money market wire orders.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker kann keine telegrafischen Bestellungen für den Geldmarkt eingeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite al corredor introducir órdenes de transferencias cablegráficas del mercado monetario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier n'est pas autorisé à entrer des ordres électroniques du marché monétaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaar mag geen telegrafische orders voor de geldmarkt invoeren")); }

        // Actions
	};
}



