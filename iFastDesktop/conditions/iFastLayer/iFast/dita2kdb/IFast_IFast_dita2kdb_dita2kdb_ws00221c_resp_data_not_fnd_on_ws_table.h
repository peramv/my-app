#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_data_not_fnd_on_ws_table : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_data_not_fnd_on_ws_table() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_data_not_fnd_on_ws_table() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DATA_NOT_FND_ON_WS_TABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Scheduled payment at the end of month will not be made.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Scheduled payment at the end of month will not be made.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Planmäßige Zahlung am Ende des Monats wird nicht erfolgen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El pago programado al final del mes no se realizará.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le versement périodique à la fin du mois ne sera pas fait.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geplande betaling aan het eind van de maand wordt niet gedaan")); }

        // Actions
	};
}



