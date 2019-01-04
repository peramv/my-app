#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_net_dlr_code_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_net_dlr_code_not_allowed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_net_dlr_code_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_NET_DLR_CODE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please input Birth Name.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Please input Birth Name.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bitte geben Sie den Geburtsnamen ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Por favor introduzca el nombre al nacimiento")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez saisir le nom à la naissance.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voer geboortenaam in")); }

        // Actions
	};
}



