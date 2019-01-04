#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_contract_available_to_shaareholder_group : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_contract_available_to_shaareholder_group() { }
		~CIFast_IFast_ifastcbo_err_no_contract_available_to_shaareholder_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_CONTRACT_AVAILABLE_TO_SHAAREHOLDER_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Contracts available to shareholder group.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Verträge für Aktionärsgruppe verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay contratos disponibles para el grupo de accionistas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun contrat disponible pour le groupe d'actionnaires")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen overeenkomsten beschikbaar voor aandeelhoudersgroep")); }

        // Actions
	};
}



