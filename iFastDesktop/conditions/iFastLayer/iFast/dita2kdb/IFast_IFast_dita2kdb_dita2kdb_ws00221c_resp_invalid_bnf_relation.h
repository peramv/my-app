﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bnf_relation : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bnf_relation() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bnf_relation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_BNF_RELATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Back Office Time Zone is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Back Office Time Zone is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Abrechnungsstellen-Zeitzone ist ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La zona horaria de back office no es válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fuseau horaire du suivi de marché est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige tijdszone back office")); }

        // Actions
	};
}



