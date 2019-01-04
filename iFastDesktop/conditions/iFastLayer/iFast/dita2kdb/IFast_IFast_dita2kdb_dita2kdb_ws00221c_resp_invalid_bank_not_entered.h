#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_not_entered : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_not_entered() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_not_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_BANK_NOT_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Account Owner Entities should be setup for Joint Account Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Multiple Account Owner Entities should be setup for Joint Account Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrfach-Kontoinhaber-Objekt sollte für Gemeinsachtskontoart erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Propietarios de cuenta múltiples para el tipo de cuenta Conjunta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plusieurs titulaires du compte doivent être créés pour le type de compte Conjoint.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet een eenheid voor meerdere accounthouders worden ingesteld voor het type Gezamenlijke account")); }

        // Actions
	};
}



