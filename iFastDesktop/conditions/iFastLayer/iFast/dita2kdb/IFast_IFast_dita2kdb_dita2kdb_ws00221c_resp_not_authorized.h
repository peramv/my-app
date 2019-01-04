#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_not_authorized : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_not_authorized() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_not_authorized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_NOT_AUTHORIZED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Province file records not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Province file records not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provinz-Dateieinträge nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los registros de archivo de provincia no están disponibles")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les enregistrements du fichier de la province ne sont pas disponibles.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen records voor het provinciebestand beschikbaar")); }

        // Actions
	};
}



