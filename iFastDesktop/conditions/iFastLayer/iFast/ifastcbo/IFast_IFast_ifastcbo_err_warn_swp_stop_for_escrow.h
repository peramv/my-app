#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_swp_stop_for_escrow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_swp_stop_for_escrow() { }
		~CIFast_IFast_ifastcbo_err_warn_swp_stop_for_escrow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_SWP_STOP_FOR_ESCROW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SWP exists for this Escrow/Assigned account. All active SWP will be stopped automatically.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SWP existiert für dieses Escrow-Konto (Anderkonto). Alle aktiven SWP werden automatisch gestoppt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existe SWP para esta cuenta de custodia. Toda la SWP activa se detendrá automáticamente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un PRP existe pour ce compte cédé en garantie. Tout les PRP actifs seront arrêtés automatiquement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("SWP bestaat voor dit pandaccount. Alle actieve SWP's worden automatisch beëindigd")); }

        // Actions
	};
}



