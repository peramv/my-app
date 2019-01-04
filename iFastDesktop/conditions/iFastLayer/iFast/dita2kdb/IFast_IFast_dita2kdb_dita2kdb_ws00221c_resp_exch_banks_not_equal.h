#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_banks_not_equal : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_banks_not_equal() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_banks_not_equal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_EXCH_BANKS_NOT_EQUAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Salesperson is not permitted new business activity.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Salesperson is not permitted new business activity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter ist nicht für eine neue Geschäftstätigkeit zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite a este vendedor nueva actividad comercial")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le représentant des ventes n'est pas autorisé à faire de nouvelles affaires.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordiger mag geen nieuwe bedrijfsactiviteit aangaan")); }

        // Actions
	};
}



