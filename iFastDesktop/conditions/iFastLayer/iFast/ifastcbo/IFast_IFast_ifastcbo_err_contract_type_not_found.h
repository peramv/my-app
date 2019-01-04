#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_contract_type_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_contract_type_not_found() { }
		~CIFast_IFast_ifastcbo_err_contract_type_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_TYPE_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Type not found. Cannot create Seg Fund Contract.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Contract Type not found. Cannot create Seg Fund Contract.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vertragsart nicht gefunden. Seg Fund-Vertrag kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el tipo de contrato. No se puede crear el contrato de fondo segregado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de contrat introuvable. Impossible de créer un contrat de fonds distincts.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overeenkomsttype is niet gevonden. Afzonderlijke fondsovereenkomst kon niet worden gemaakt")); }

        // Actions
	};
}



