#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_unissued_shrs : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_unissued_shrs() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_unissued_shrs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_UNISSUED_SHRS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate must have only two decimal digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Rate must have only two decimal digits.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Satz darf nur zwei Dezimalstellen haben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa sólo debe tener dos dígitos decimales.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux ne doit avoir que deux caractères numériques décimaux.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tarief mag slechts twee cijfers achter de komma hebben")); }

        // Actions
	};
}



