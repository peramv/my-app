#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_asset_target_rt : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_asset_target_rt() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_asset_target_rt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ASSET_TARGET_RT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account entity not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account entity not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Objekt nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la entidad de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Entité du compte introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounteenheid is niet gevonden")); }

        // Actions
	};
}



