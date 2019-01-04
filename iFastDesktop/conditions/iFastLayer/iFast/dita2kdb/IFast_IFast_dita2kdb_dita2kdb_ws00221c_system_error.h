#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_system_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_system_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_system_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_SYSTEM_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Corresponding Fund Information not found, please contact technical support.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Corresponding Fund Information not found, please contact technical support.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entsprechende Fonds-Informationen nicht gefunden, wenden Sie sich bitte an den technischen Support.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la información del fondo correspondiente, por favor póngase en contacto con el soporte técnico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le fonds correspondant est introuvable. Veuillez communiquer avec le soutien technique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijbehorende fondsgegevens zijn niet gevonden, neem contact op met de technische dienst")); }

        // Actions
	};
}



