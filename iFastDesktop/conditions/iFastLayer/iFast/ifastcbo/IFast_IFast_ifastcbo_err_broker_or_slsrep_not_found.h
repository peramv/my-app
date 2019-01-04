#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_broker_or_slsrep_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_broker_or_slsrep_not_found() { }
		~CIFast_IFast_ifastcbo_err_broker_or_slsrep_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_OR_SLSREP_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker Code or Sales Representative Code does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker-Code oder Verkaufsvertreter-Code existiert nicht, bitte neu eingeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de corredor o de representante de ventas no existe, por favor vuelva a introducirlo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de courtier ou de représentant des ventes est inexistant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaarscode of vertegenwoordigerscode bestaat niet, vul opnieuw in")); }

        // Actions
	};
}



