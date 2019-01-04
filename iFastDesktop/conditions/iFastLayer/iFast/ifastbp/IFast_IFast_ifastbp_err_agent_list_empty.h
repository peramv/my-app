#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_err_agent_list_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_err_agent_list_empty() { }
		~CIFast_IFast_ifastbp_err_agent_list_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGENT_LIST_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No agents for the broker %broker% and branch %branch%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun agent pour le courtier %broker% et la succursale %branch%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Vertreter für den Broker %broker% und Filiale %branch%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay agentes para el corredor %broker% y sucursal %branch%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun représentant pour le courtier %broker% et l'unité de service %branch%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen agenten voor makelaar %broker% en filiaal %branch%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Select anther broker or branch")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Selectionnez un autre courtier ou une autre succursale.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie einen anderen Broker oder eine andere Filiale aus")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Select anther broker or branch")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Sélectionnez un autre courtier ou une autre unité de service.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Selecteer een andere makelaar of een ander filiaal")); }
	};
}



