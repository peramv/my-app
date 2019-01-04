#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_excess_table_data : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_excess_table_data() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_excess_table_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_EXCESS_TABLE_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity address record not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entity address record not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt-Adresseneintrag nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de dirección de entidad no está disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de l'adresse de l'entité n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record eenheidsadres is niet beschikbaar")); }

        // Actions
	};
}



