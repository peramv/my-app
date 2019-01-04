#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_end_of_data : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_end_of_data() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_end_of_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_END_OF_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("End of data reached.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("End of data reached.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenende erreicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se llegó al final de los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fin des données")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einde gegevens bereikt")); }

        // Actions
	};
}



