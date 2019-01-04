#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_row_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_row_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_row_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_ROW_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Min/Max Information cannot be determined for future date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Min/Max Information cannot be determined for future date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Min/Max-Informationen können für ein zukünftiges Datum nicht festgelegt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede determinar la información mínima/máxima para una fecha futura.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information min/max ne peut être déterminée pour une date ultérieure.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Min./max. gegevens kunnen niet worden vastgesteld voor toekomstige datum")); }

        // Actions
	};
}



