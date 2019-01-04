#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_social_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_social_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_social_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SOCIAL_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
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



