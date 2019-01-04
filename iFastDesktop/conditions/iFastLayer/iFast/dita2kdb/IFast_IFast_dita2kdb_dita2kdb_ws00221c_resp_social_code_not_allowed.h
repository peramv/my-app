#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_allowed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_SOCIAL_CODE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum allowable SWP amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Minimum allowable SWP amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimal erlaubte SWP-Anzahl für Fonds %FUNDNAME% beträgt  %AMOUNT%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto SWP  mínimo permitido para el fondo %FUNDNAME% es %AMOUNT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de PRP minimal autorisé pour le fonds %FUNDNAME% est %AMOUNT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegestane minimum SWP-bedrag voor fonds %FUNDNAME% is %AMOUNT%")); }

        // Actions
	};
}



