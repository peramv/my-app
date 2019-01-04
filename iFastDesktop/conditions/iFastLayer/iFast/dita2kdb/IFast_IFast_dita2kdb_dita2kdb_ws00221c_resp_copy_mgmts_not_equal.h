#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_mgmts_not_equal : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_mgmts_not_equal() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_mgmts_not_equal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_COPY_MGMTS_NOT_EQUAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This shareholder is less than 69 years old.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This shareholder is less than 69 years old.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieser Aktionär ist jünger als 69.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este accionista tiene menos de 69 años.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cet actionnaire a moins de 69 ans.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deze aandeelhouder is jonger dan 69 jaar")); }

        // Actions
	};
}



