﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_option : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_option() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_option() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_FUND_OPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Address Code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Address Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Adresscode.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de dirección no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'adresse invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige adrescode")); }

        // Actions
	};
}



