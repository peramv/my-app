#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_individual_id : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_individual_id() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_individual_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_INDIVIDUAL_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RRIF Information already exists for specified year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RRIF Information already exists for specified year.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RRIF-Information für das angegebene Jahr bereits vorhanden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información RRIF ya existe para el año especificado")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information FERR déjà existante pour l'année spécifiée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("RRIF-gegevens bestaan al voor het opgegeven jaar")); }

        // Actions
	};
}



