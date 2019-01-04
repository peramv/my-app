﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notopen : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notopen() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notopen() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_NOTOPEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELDNAME% is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FIELDNAME% is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELDNAME% ist ungültig. Geben Sie einen gültigen Wert ein oder drücken Sie F4, um nach einem gültigen Wert zu suchen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELDNAME% no es válido. Introduzca un valor válido o presione F4 para buscar un valor válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELDNAME% est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELDNAME% is ongeldig. Geef een geldige waarde op of druk op F4 voor een geldige waarde")); }

        // Actions
	};
}



