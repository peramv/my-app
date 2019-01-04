#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_unit_redeem_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_unit_redeem_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_net_unit_redeem_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_UNIT_REDEEM_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net redemption in units is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Netto-Tilgung in Anteil ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el rescate neto en unidad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat net en unités n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Netto aflossing in eenheid is niet toegestaan")); }

        // Actions
	};
}



