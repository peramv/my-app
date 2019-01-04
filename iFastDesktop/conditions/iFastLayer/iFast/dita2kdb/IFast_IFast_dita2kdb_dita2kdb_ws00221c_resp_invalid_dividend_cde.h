#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dividend_cde : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dividend_cde() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dividend_cde() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_DIVIDEND_CDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transit Number exceeds allowable number of digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transit Number exceeds allowable number of digits.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankleitzahl überschreitet die erlaubte Anzahl der Ziffern.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de tránsito excede la cantidad de dígitos permitida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de succursale excède le nombre de caractères numériques autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transitnummer overschrijdt toegestane aantal cijfers")); }

        // Actions
	};
}



