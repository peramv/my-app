#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_marital_status : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_marital_status() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_marital_status() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_MARITAL_STATUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("System is not configured for Date and Time Time Zone Conversion.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("System is not configured for Date and Time Time Zone Conversion.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("System ist für Datums- und Zeitzonen-Umstellung nicht konfiguriert")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no está configurado para la conversión de fechas y zonas horarias")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système n'est pas configuré pour la conversion de fuseau horaire de la date et de l'heure.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem is niet geconfigureerd voor de conversie van datum- en tijdzones")); }

        // Actions
	};
}



