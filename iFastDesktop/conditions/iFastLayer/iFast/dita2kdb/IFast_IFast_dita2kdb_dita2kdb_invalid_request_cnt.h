#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_request_cnt : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_request_cnt() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_request_cnt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_REQUEST_CNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - After mandatory logoff time.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Le temps de deconnexion obligatoire est depasse.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Nach der vorgeschriebenen Abmeldezeit.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Después del tiempo de desconexión obligatorio")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – délai obligatoire de fermeture de session dépassé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Na verplichte afmeldtijd")); }

        // Actions
	};
}



