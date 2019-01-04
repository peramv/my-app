#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_socket_initialization_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_socket_initialization_failed() { }
		~CIFast_IFast_ifastdbrkr_err_socket_initialization_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SOCKET_INITIALIZATION_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RTS socket connection failed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verbindungsanfrage-Sockelverbindung fehlgeschlagen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falló la conexión con el socket RTS.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de la connection du port RTS")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Socketverbinding RTS is mislukt")); }

        // Actions
	};
}



