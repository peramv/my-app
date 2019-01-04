#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_not_for_bel_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_not_for_bel_fund() { }
		~CIFast_IFast_ifastcbo_err_net_not_for_bel_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_NOT_FOR_BEL_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net is not allowed for a back end load fund.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Net is not allowed for Back End Load Fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Netto ist für einen Hohe Endkosten-Fonds nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite Neto para un fondo con cargo de venta final")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Net non autorisé pour un fonds avec frais de rachat")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Netto is niet toegestaan voor een Back End Load fonds")); }

        // Actions
	};
}



