#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_access_method : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_access_method() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_access_method() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ACCESS_METHOD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The calculated value for this field is %CALCULATED%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The calculated value for this field is %CALCULATED%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der errechnete Wert für dieses Feld ist %CALCULATED%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor calculado para este campo es %CALCULATED%..")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur calculée pour ce champ est %CALCULATED%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De berekende waarde voor dit veld is %CALCULATED%")); }

        // Actions
	};
}



