#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_function_type : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_function_type() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_function_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_FUNCTION_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch is not active or does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batch is not active or does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch ist nicht aktiv oder existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El lote no está activo o no existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le lot est inactif ou n'existe pas.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batch is niet actief of bestaat niet")); }

        // Actions
	};
}



