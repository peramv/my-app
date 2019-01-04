#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_br_summry : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_br_summry() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_br_summry() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_DLR_BR_SUMMRY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid province of registration.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Region d'enregistrement invalide")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Registrierungs-Provinz.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Provincia de registro no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Province d'enregistrement invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige registratieprovincie")); }

        // Actions
	};
}



