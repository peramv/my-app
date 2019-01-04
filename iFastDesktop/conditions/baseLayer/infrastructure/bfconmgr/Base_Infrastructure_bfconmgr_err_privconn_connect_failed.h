#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfconmgr_err_privconn_connect_failed : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfconmgr_err_privconn_connect_failed() { }
		~CBase_Infrastructure_bfconmgr_err_privconn_connect_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIVCONN_CONNECT_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfconmgr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("End of data reached.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("End of data reached.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenende erreicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El contenedor de AWD ya está abierto.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le conteneur AWD est déjà ouvert.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-container is al geopend")); }

        // Actions
	};
}



