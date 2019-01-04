#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_eml_adr_entered : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_eml_adr_entered() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_eml_adr_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_EML_ADR_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to assign Confirmation Number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to assign Confirmation Number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bestätigungsnummer kann nicht zugewiesen werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible asignar un número de confirmación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'attribuer un numéro de confirmation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bevestigingsnummer kon niet worden toegewezen")); }

        // Actions
	};
}



