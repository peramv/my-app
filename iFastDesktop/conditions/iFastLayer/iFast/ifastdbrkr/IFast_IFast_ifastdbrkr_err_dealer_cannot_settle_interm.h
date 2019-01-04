#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_dealer_cannot_settle_interm : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_dealer_cannot_settle_interm() { }
		~CIFast_IFast_ifastdbrkr_err_dealer_cannot_settle_interm() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEALER_CANNOT_SETTLE_INTERM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dealer cannot settle orders placed by Intermediary.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Händler kann Aufträge von Mittlern nicht abrechnen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El agente no puede liquidar órdenes colocadas por el intermediario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier ne peut régler des ordres placés par l'intermédiaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handelaar kan geen orders betalen die door tussenpersoon zijn geplaatst")); }

        // Actions
	};
}



